#include "manualcontrol.h"
#include "ui_manualcontrol.h"

ManualControl::ManualControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManualControl)
{
    ui->setupUi(this);
}

ManualControl::~ManualControl()
{
    delete ui;
}
