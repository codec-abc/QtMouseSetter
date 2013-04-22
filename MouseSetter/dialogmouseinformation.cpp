#include "dialogmouseinformation.h"
#include "ui_dialogmouseinformation.h"

DialogMouseInformation::DialogMouseInformation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMouseInformation)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(),this->geometry().height());
}

DialogMouseInformation::~DialogMouseInformation()
{
    delete ui;
}

Ui::DialogMouseInformation* DialogMouseInformation::getUI()
{
    return ui;
}
