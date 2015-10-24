#include "printerconfigs.h"
#include "ui_printerconfigs.h"

PrinterConfigs::PrinterConfigs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrinterConfigs)
{
    ui->setupUi(this);
}

PrinterConfigs::~PrinterConfigs()
{
    delete ui;
}
