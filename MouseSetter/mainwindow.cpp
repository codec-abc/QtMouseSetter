#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windows.h"
#include <iostream>
#include "ui_dialogMouseInformation.h"
#include <QMenu>
#include <QCloseEvent>
#include <QSettings>
#include "dialogabout.h"
#include "dialogoption.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) ,
    settings(new QSettings("codec-abc", "MouseSetter")),
    lastClose(false)
{
    ui->setupUi(this);
    trayIconMenu = new QMenu(this);
    subMenuTrayIcon = new QMenu(this);
    subMenuTrayIcon->setTitle("Switch to profile");
    subMenuTrayIcon->setEnabled(false);
    createActions();
    createTrayIcon();
    setIcon();
    trayIcon->show();
    bool value = settings->value("showMainWindowAtStartup",true).toBool();
    if(value)
    {
        this->show();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete settings;
}

void MainWindow::on_MouseInfoButton_clicked()
{

}

void MainWindow::displayMouseInformationPopup()
{
    int aMouseInfo[3];
    int bMouseInfo = -1;
    SystemParametersInfo(SPI_GETMOUSE, 0,&aMouseInfo,0);
    SystemParametersInfo(SPI_GETMOUSESPEED,0,&bMouseInfo,0);
    QDialog* dialogMouseInformation = new QDialog(0,0);
    Ui::Dialog dialogMouseInformationUi;

    QString string1 = QString::number(aMouseInfo[0]);
    QString string2 = QString::number(aMouseInfo[1]);
    QString string3 = QString::number(aMouseInfo[2]);
    QString string4 = QString::number(bMouseInfo);

    dialogMouseInformationUi.setupUi(dialogMouseInformation);

    dialogMouseInformationUi.mouse_threshold_0_label->setText(string1);
    dialogMouseInformationUi.mouse_threshold_1_label->setText(string2);
    dialogMouseInformationUi.mouse_acceleration_label->setText(string3);
    dialogMouseInformationUi.mouse_speed_label->setText(string4);

    dialogMouseInformation->show();
}

//void MainWindow::on_pushButton_4_clicked()
//{
//    int aMouseInfo[3];
//    int bMouseInfo=ui->horizontalSlider->value();
//    if(!bMouseInfo != 1)
//    {
//        bMouseInfo = (bMouseInfo -1)*2;
//    }
//    if(!ui->checkBox->isChecked())
//    {
//        aMouseInfo[0]=0;
//        aMouseInfo[1]=0;
//        aMouseInfo[2]=0;
//    }
//    else
//    {
//        aMouseInfo[0]=6;
//        aMouseInfo[1]=10;
//        aMouseInfo[2]=1;
//    }
//    SystemParametersInfo(SPI_SETMOUSE,0,aMouseInfo,SPIF_SENDWININICHANGE);
//    SystemParametersInfo(SPI_SETMOUSESPEED, 0, (int*) bMouseInfo, SPIF_SENDWININICHANGE);
//}

void MainWindow::setIcon()
{
    trayIcon->setIcon(QIcon(":/Resource/input-mouse.png"));
}

void MainWindow::createTrayIcon()
{
    trayIconMenu->addAction(open);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(close);
    trayIconMenu->addMenu(this->subMenuTrayIcon);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);

    connect(
            trayIcon,
            SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,
            SLOT(trayIconClicked(QSystemTrayIcon::ActivationReason))
           );
    connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));

}

void MainWindow::trayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::Trigger)
    {
        this->show();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible())
    {
        bool value = settings->value("showTrayIconMessage",true).toBool();
        if(value && !lastClose)
        {
            trayIcon->showMessage(tr("Mouse Profile Switcher"),
            tr("This application is still running. Click this to hide the message for the next time"));
        }
        hide();
        event->ignore(); // Don't let the event propagate to the base class
    }
}

void MainWindow::createActions()
{
    open = new QAction(tr("&Open"), this);
    connect(open, SIGNAL(triggered()), this, SLOT(show()));

    close = new QAction(tr("&Quit"), this);
    connect(close, SIGNAL(triggered()), this, SLOT(exitApp()));
}


void MainWindow::on_actionAbout_triggered()
{
    DialogAbout Dialog(this);
    Dialog.setModal(true);
    Dialog.exec();
}

void MainWindow::on_actionPreferences_triggered()
{
    DialogOption Dialog(this);
    Dialog.setModal(true);
    Dialog.exec();
}

QSettings* MainWindow::getSetting()
{
    return this->settings;
}

void MainWindow::messageClicked()
{
    settings->setValue("showTrayIconMessage",false);
}

void MainWindow::exitApp()
{
    lastClose=true;
    qApp->quit();
}
