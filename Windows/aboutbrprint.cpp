
#include "aboutbrprint.h"
#include "ui_aboutbrprint.h"
#include "BrPrint3D.h"
#include "QCloseEvent"

aboutBrPrint::aboutBrPrint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::aboutBrPrint)
{
    ui->setupUi(this);

}

aboutBrPrint::~aboutBrPrint()
{
    delete ui;
}

