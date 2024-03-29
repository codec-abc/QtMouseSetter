#include "dialogaddprofile.h"
#include "ui_dialogaddprofile.h"
#include "mouseprofile.h"
#include "mainwindow.h"
#include <iostream>
#include <QMessageBox>

DialogAddProfile::DialogAddProfile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddProfile)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(),this->geometry().height());
    this->ui->frame->setEnabled(true);
}

DialogAddProfile::~DialogAddProfile()
{
    delete ui;
}

void DialogAddProfile::on_buttonBox_accepted()
{

}

void DialogAddProfile::accept()
{
    int a0;
    int a1;
    int a2;
    int a3;

    QString name = this->ui->lineEdit->text();
    if(!this->ui->radioButton_3) // custom profile
    {
        a0=this->ui->spinBox->value();
        a1=this->ui->spinBox_2->value();
        a2=this->ui->spinBox_3->value();
        a3=this->ui->spinBox_4->value();
    }
    else
    {
        a3=ui->horizontalSlider->value();
        if(!a3 != 1)
        {
            a3 = (a3 -1)*2;
        }
           if(!ui->checkBox->isChecked())
           {
               a0=0;
               a1=0;
               a2=0;
           }
           else
           {
               a0=6;
               a1=10;
               a2=1;
           }
    }
    if(!name.isEmpty())
    {
        MouseProfile profile(a0,a1,a2,a3,name);
        MainWindow* mainWindow = (MainWindow*) this->parent();
        bool profileSuccefullyAdded = mainWindow->addProfile(profile);
        if(profileSuccefullyAdded)
        {
            QDialog::accept();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText("this name already exist, please choose another one");
            msgBox.exec();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Please, give a name to this profile");
        msgBox.exec();
    }

}

void DialogAddProfile::on_radioButton_4_toggled(bool checked)
{
    this->ui->frame->setEnabled(checked);
}

void DialogAddProfile::on_radioButton_3_toggled(bool checked)
{
    this->ui->frame_5->setEnabled(checked);
}
