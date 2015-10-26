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

PrinterConfigs::init(QSettings settings)
{
    //Load the previous configs if them exists
    QStringList groups;
    settings.beginGroup("Printer_Configs");
    groups = settings.childGroups();
    settings.endGroup();
    ui->cb_printer->addItems(groups);
    if(!groups.isEmpty())
    {   //Criar init printer configs
        QString a = ui->cb_printer->currentText();
        loadConfigs(a);
        //Connection Tab
        ui->cb_Connection_Type->setCurrentText(this->connectionType);
        ui->cb_Transmition_Rate->setCurrentText(this->transmissionRate);
        ui->cb_Firmware->setCurrentText(this->firmwareType);
        ui->cb_Cache_Size->setCurrentText(this->cacheSize);

        //Resets
        ui->ck_resetonConnect->setChecked(this->resetOnConnect);
        ui->ck_resetonEmergency->setChecked(this->resetOnEmergency);
        ui->ck_logImpressao->setChecked(this->printLog);

        //Printer Tab
        ui->tb_RateMoviment->setText(this->rateMoviment);
        ui->tb_FeedZ->setText(this->feedZ);
        ui->tb_ExtruderSpeed_Sec->setText(this->extruderSpeed);
        ui->tb_extruder_vol_max->setText(this->extruderMAXVol);
        ui->tb_SpeedRetraction->setText(this->extruderRetraction);
        ui->tb_Table_Temperature->setText(this->bedTemperature);
        ui->tb_ExtruderTemperature->setText(this->extruderTemperature);
        ui->tb_AreaPrint_X->setText(this->areaX);
        ui->tb_AreaPrint_Y->setText(this->areaY);
        ui->tb_AreaPrint_Z->setText(this->areaZ);

        //Extruder Tab
        ui->cb_Extruder_qnt->setCurrentText(this->extruderQnt);
        ui->tb_extruderMaxTemp->setText(this->extruderMAXTemp);
        ui->tb_bedMaxTemp->setText(this->bedMAXTemp);
        ui->tb_extruder_vol_max->setText(this->extruderMAXVol);
    }

}
