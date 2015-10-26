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

void PrinterConfigs::init(QSettings *settings)
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

void PrinterConfigs::on_bt_saveConfig_clicked() //Salva as configurações de impressoras
{   bool ok;
    QString name = QInputDialog::getText(this, tr("Insert the name of config: "),tr("Name:"),QLineEdit::Normal,"ex.: Graber1",&ok);
    this->settings.beginGroup("Printer_Configs");
    if(ok && !name.isEmpty())
    {
        this->settings.beginGroup(name);
        //Conexao
        this->settings.setValue("Firmware",ui->cb_Firmware->currentText());
        this->settings.setValue("ResetOnConnect",ui->ck_resetonConnect->checkState());
        this->settings.setValue("ResetonEmergency",ui->ck_resetonEmergency->checkState());
        this->settings.setValue("CacheSize", ui->cb_Cache_Size->currentText());
        this->settings.setValue("TransmissionRate",ui->cb_Transmition_Rate->currentText());
        this->settings.setValue("PrinterLog", ui->ck_logImpressao->checkState());
        //Impressora
        this->settings.setValue("RateMoviment",ui->tb_RateMoviment->text());
        this->settings.setValue("FeedZ",ui->tb_FeedZ->text());
        this->settings.setValue("ExtruderSpeed",ui->tb_ExtruderSpeed_Sec->text());
        this->settings.setValue("ExtruderRetraction",ui->tb_SpeedRetraction->text());
        this->settings.setValue("BedTemperature",ui->tb_Table_Temperature->text());
        this->settings.setValue("ExtruderTemperature",ui->tb_ExtruderTemperature->text());
        this->settings.setValue("AreaX",ui->tb_AreaPrint_X->text());
        this->settings.setValue("AreaY",ui->tb_AreaPrint_Y->text());
        this->settings.setValue("AreaZ",ui->tb_AreaPrint_Z->text());
        //Extrusor
        this->settings.setValue("ExtruderQnt",ui->cb_Extruder_qnt->currentText());
        this->settings.setValue("ExtruderMaxTemp",ui->tb_extruderMaxTemp->text());
        this->settings.setValue("BedMaxTemp",ui->tb_bedMaxTemp->text());
        this->settings.setValue("VolumeMax",ui->tb_extruder_vol_max->text());
        this->settings.endGroup();

    }
    this->settings.endGroup();
    QStringList groups;
    this->settings.beginGroup("Printer_Configs");
    groups = this->settings.childGroups();
    this->settings.endGroup();
    ui->cb_printer->clear();
    ui->cb_printer->addItems(groups);
}
