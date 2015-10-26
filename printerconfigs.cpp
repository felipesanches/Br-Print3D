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

void PrinterConfigs::init(QSettings settings)
{   this->settings = settings;
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

void BrPrint3D::on_bt_saveConfig_clicked() //Salva as configurações de impressoras
{   bool ok;
    QString name = QInputDialog::getText(this, tr("Insert the name of config: "),tr("Nome:"),QLineEdit::Normal,"ex.: Graber1",&ok);
    settings.beginGroup("Printer_Configs");
    if(ok && !name.isEmpty())
    {
        settings.beginGroup(name);
        //Conexao
        settings.setValue("Firmware",ui->cb_Firmware->currentText());
        settings.setValue("ResetOnConnect",ui->ck_resetonConnect->checkState());
        settings.setValue("ResetonEmergency",ui->ck_resetonEmergency->checkState());
        settings.setValue("CacheSize", ui->cb_Cache_Size->currentText());
        settings.setValue("TransmissionRate",ui->cb_Transmition_Rate->currentText());
        settings.setValue("PrinterLog", ui->ck_logImpressao->checkState());
        //Impressora
        settings.setValue("RateMoviment",ui->tb_RateMoviment->text());
        settings.setValue("FeedZ",ui->tb_FeedZ->text());
        settings.setValue("ExtruderSpeed",ui->tb_ExtruderSpeed_Sec->text());
        settings.setValue("ExtruderRetraction",ui->tb_SpeedRetraction->text());
        settings.setValue("BedTemperature",ui->tb_Table_Temperature->text());
        settings.setValue("ExtruderTemperature",ui->tb_ExtruderTemperature->text());
        settings.setValue("AreaX",ui->tb_AreaPrint_X->text());
        settings.setValue("AreaY",ui->tb_AreaPrint_Y->text());
        settings.setValue("AreaZ",ui->tb_AreaPrint_Z->text());
        //Extrusor
        settings.setValue("ExtruderQnt",ui->cb_Extruder_qnt->currentText());
        settings.setValue("ExtruderMaxTemp",ui->tb_extruderMaxTemp->text());
        settings.setValue("BedMaxTemp",ui->tb_bedMaxTemp->text());
        settings.setValue("VolumeMax",ui->tb_extruder_vol_max->text());
        settings.endGroup();

    }
    settings.endGroup();
    QStringList groups;
    settings.beginGroup("Printer_Configs");
    groups = settings.childGroups();
    settings.endGroup();
    ui->cb_printer->clear();
    ui->cb_printer->addItems(groups);
}
