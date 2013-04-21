#include "dialogoption.h"
#include "ui_dialogoption.h"
#include "mainwindow.h"
#include <QSettings>
#include "windows.h"
#include <iostream>

DialogOption::DialogOption(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOption)
{
    ui->setupUi(this);
    init();
}

DialogOption::~DialogOption()
{
    delete ui;
}

void DialogOption::init()
{
    MainWindow* mainWindow = (MainWindow*) this->parent();
    QSettings* settings = mainWindow->getSetting();
    QString test = QSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat).value("MouseSetter").toString();
    std::cout << test.toStdString() << std::endl;
    QString test2 = QCoreApplication::applicationFilePath();
    std::cout << test2.toStdString() << std::endl;
    bool value = test == test2;
    bool value2 = settings->value("showMainWindowAtStartup",true).toBool();
    bool value3 = settings->value("showTrayIconMessage",true).toBool();

    ui->checkBox->setChecked(value);
    ui->checkBox_2->setChecked(value2);
    ui->checkBox_3->setChecked(value3);

}

void DialogOption::on_buttonBox_accepted()
{
    bool value = ui->checkBox->isChecked();
    bool value2 = ui->checkBox_2->isChecked();
    bool value3 = ui->checkBox_3->isChecked();

    MainWindow* mainWindow = (MainWindow*) this->parent();
    QSettings* settings = mainWindow->getSetting();

    if(value2)
    {

        settings->setValue("showMainWindowAtStartup",true);
    }
    if(!value2)
    {
        settings->setValue("showMainWindowAtStartup",false);
    }

    if(value3)
    {
        settings->setValue("showTrayIconMessage",true);
    }
    if(!value3)
    {
        settings->setValue("showTrayIconMessage",false);
    }
    if(value)
    {
        QSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat).setValue("MouseSetter",QCoreApplication::applicationFilePath());
    }
    if(!value)
    {
        QSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat).remove("MouseSetter");
    }
}
