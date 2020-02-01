#include "aboutframe.h"
#include "ui_aboutframe.h"

aboutframe::aboutframe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutframe)
{
    ui->setupUi(this);
}

aboutframe::~aboutframe()
{
    delete ui;
}
