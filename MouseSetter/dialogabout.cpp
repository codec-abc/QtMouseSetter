#include "dialogabout.h"
#include "ui_dialogabout.h"

DialogAbout::DialogAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAbout)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(),this->geometry().height());
}

DialogAbout::~DialogAbout()
{
    delete ui;
}
