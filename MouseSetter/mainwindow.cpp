#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windows.h"
#include <iostream>
#include "ui_dialogMouseInformation.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//        SystemParametersInfo(SPI_SETMOUSE,0,aMouseInfo,SPIF_SENDCHANGE);

void MainWindow::on_MouseInfoButton_clicked()
{
    BOOL fResult1;
    BOOL fResult2;
    int aMouseInfo[3];
    int bMouseInfo = -1;
    fResult1 = SystemParametersInfo(SPI_GETMOUSE, 0,&aMouseInfo,0);
    fResult2 = SystemParametersInfo(SPI_GETMOUSESPEED,0,&bMouseInfo,0);
    std::cout << "push button clicked" << std::endl;
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

   // dialogMouseInformation->layout()->setSizeConstraint( QLayout::SetFixedSize );
    dialogMouseInformation->show();

}
