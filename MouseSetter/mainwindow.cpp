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

void MainWindow::on_MouseInfoButton_clicked()
{

}

void MainWindow::displayMouseInformationPopup()
{
    int aMouseInfo[3];
    int bMouseInfo = -1;
    SystemParametersInfo(SPI_GETMOUSE, 0,&aMouseInfo,0);
    SystemParametersInfo(SPI_GETMOUSESPEED,0,&bMouseInfo,0);
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

    dialogMouseInformation->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    int aMouseInfo[3];
    int bMouseInfo=ui->horizontalSlider->value();
    if(!bMouseInfo != 1)
    {
        bMouseInfo = (bMouseInfo -1)*2;
    }
    if(!ui->checkBox->isChecked())
    {
        aMouseInfo[0]=0;
        aMouseInfo[1]=0;
        aMouseInfo[2]=0;
    }
    else
    {
        aMouseInfo[0]=6;
        aMouseInfo[1]=10;
        aMouseInfo[2]=1;
    }
    SystemParametersInfo(SPI_SETMOUSE,0,aMouseInfo,SPIF_SENDWININICHANGE);
    SystemParametersInfo(SPI_SETMOUSESPEED, 0, (int*) bMouseInfo, SPIF_SENDWININICHANGE);
    std::cout << "mouse speed set to " << bMouseInfo << std::endl;
}
