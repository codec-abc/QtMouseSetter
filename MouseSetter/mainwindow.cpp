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
#include "dialogaddprofile.h"

const QString MainWindow::profilePrefix("Profile");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) ,
    settings(new QSettings("codec-abc", "MouseSetter")),
    lastClose(false),
    signalMapper(new QSignalMapper(this))


{
    ui->setupUi(this);
    trayIconMenu = new QMenu(this);
    subMenuTrayIcon = new QMenu(this);
    subMenuTrayIcon->setTitle("Switch to profile");
    createActions();
    createTrayIcon();
    setIcon();
    trayIcon->show();
    bool value = settings->value("showMainWindowAtStartup",true).toBool();
    if(value)
    {
        this->show();
    }
    this->updateProfiles();



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
    trayIconMenu->addMenu(this->subMenuTrayIcon);
    trayIconMenu->addAction(close);


    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);

    connect(
            trayIcon,
            SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,
            SLOT(trayIconClicked(QSystemTrayIcon::ActivationReason))
           );
    connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
    connect(signalMapper,
            SIGNAL(mapped(int)),
            this,
            SLOT(applyProfileFromIndex(int)));

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

void MainWindow::updateProfiles()
{
    int numberOfProfiles = settings->value("nbProfiles",0).toInt();
    this->ui->comboBox->clear();
    this->subMenuTrayIcon->clear();
    for (int i = 0; i < mouseProfileAndAction.size(); i++)
    {
        QAction* qaction = mouseProfileAndAction[i].second;
        delete qaction;
    }
    this->mouseProfileAndAction.clear();
    for (int i = 0; i < numberOfProfiles; i++)
    {
        QString currentProfileNamedIndex(QString((MainWindow::profilePrefix)).append(QString::number(i+1)));
        int a0          = settings->value(QString(currentProfileNamedIndex).append("/a0"),0).toInt();
        int a1          = settings->value(QString(currentProfileNamedIndex).append("/a1"),0).toInt();
        int a2          = settings->value(QString(currentProfileNamedIndex).append("/a2"),0).toInt();
        int a3          = settings->value(QString(currentProfileNamedIndex).append("/a3"),0).toInt();
        QString name    = settings->value(QString(currentProfileNamedIndex).append("/name"),"").toString();
        MouseProfile currentMouseProfile(a0,a1,a2,a3,name);
        std::cout << "creating action " << name.toStdString() << std::endl;
        QAction* currentAction = new QAction(name,this);
        connect(currentAction, SIGNAL(triggered()), signalMapper, SLOT(map()));
        signalMapper->setMapping(currentAction,i);

        std::pair<MouseProfile, QAction*> currentPair;
        currentPair.first = currentMouseProfile;
        currentPair.second = currentAction;
        this->mouseProfileAndAction.push_back(currentPair);
        this->ui->comboBox->addAction(currentAction);
        this->subMenuTrayIcon->addAction(currentAction);

    }
    if(numberOfProfiles > 0)
    {
        this->setButtonsState(true);
    }
    else
    {
        this->setButtonsState(false);
    }
}


void MainWindow::on_pushButtonAddProfile_clicked()
{

    DialogAddProfile Dialog(this);
    Dialog.setModal(true);
    Dialog.exec();
}

void MainWindow::addProfile(MouseProfile mouseProfileIn)
{
    int numberOfProfiles = settings->value("nbProfiles",0).toInt();
    ++numberOfProfiles;
    settings->setValue("nbProfiles",numberOfProfiles);
    QString currentProfileNamedIndex(QString((MainWindow::profilePrefix)).append(QString::number(numberOfProfiles)));
    settings->setValue(QString(currentProfileNamedIndex).append("/a0"),mouseProfileIn.a0);
    settings->setValue(QString(currentProfileNamedIndex).append("/a1"),mouseProfileIn.a1);
    settings->setValue(QString(currentProfileNamedIndex).append("/a2"),mouseProfileIn.a2);
    settings->setValue(QString(currentProfileNamedIndex).append("/a3"),mouseProfileIn.a3);
    settings->setValue(QString(currentProfileNamedIndex).append("/name"),mouseProfileIn.name);
    this->updateProfiles();
}


void MainWindow::setButtonsState(bool state)
{
    this->ui->pushButtonApplyProfile->setEnabled(state);
    this->ui->pushButtonDeleteProfile->setEnabled(state);
    this->ui->pushButtonEditProfile->setEnabled(state);
    this->ui->comboBox->setEnabled(state);
    this->subMenuTrayIcon->setEnabled(state);
}

void MainWindow::applyProfileFromIndex(int i)
{
    std::cout << "i is " << i << std::endl;
    MouseProfile mouseProfileToApply = this->mouseProfileAndAction[i].first;
    int aMouseInfo[3];
    aMouseInfo[0] = mouseProfileToApply.a0;
    aMouseInfo[1] = mouseProfileToApply.a1;
    aMouseInfo[2] = mouseProfileToApply.a2;
    int bMouseInfo=mouseProfileToApply.a3;
    SystemParametersInfo(SPI_SETMOUSE,0,aMouseInfo,SPIF_SENDWININICHANGE);
    SystemParametersInfo(SPI_SETMOUSESPEED, 0, (int*) bMouseInfo, SPIF_SENDWININICHANGE);
}
