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
//This action save the configs insert by the user on Printer Configs in Ini File
void PrinterConfigs::on_bt_saveConfig_clicked() //Save actual configs
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

void PrinterConfigs::loadConfigs(QString q)
{
        settings.beginGroup("Printer_Configs");
        settings.beginGroup(q);
        //Connection
        this->connectionType = settings.value("ConnectionType","USB").toString();
        this->transmissionRate = settings.value("TransmissionRate","115200").toString();
        this->firmwareType = settings.value("Firmware","Repetier").toString();
        this->cacheSize = settings.value("CacheSize","127").toString();
        this->resetOnConnect = settings.value("ResetOnConnect",2).toInt();
        this->resetOnEmergency = settings.value("ResetonEmergency",0).toInt();
        this->printLog = settings.value("PrinterLog",0).toInt();

        //Printer
        this->rateMoviment = settings.value("RateMoviment",0).toString();
        this->feedZ = settings.value("FeedZ",0).toString();
        this->extruderSpeed = settings.value("ExtruderSpeed",0).toString();
        this->extruderRetraction = settings.value("ExtruderRetraction",0).toString();
        this->extruderTemperature = settings.value("ExtruderTemperature",210).toString();
        this->bedTemperature = settings.value("BedTemperature",110).toString();
        this->areaX = settings.value("AreaX",0).toString();
        this->areaY = settings.value("AreaY",0).toString();
        this->areaZ = settings.value("AreaZ",0).toString();

        //Extruder
        this->extruderQnt = settings.value("ExtruderQnt",1).toString();
        this->extruderMAXTemp = settings.value("ExtruderMaxTemp",230).toString();
        this->bedMAXTemp = settings.value("BedMaxTemp",120).toString();
        this->extruderMAXVol = settings.value("VolumeMax",0).toString();
        settings.endGroup();
        settings.endGroup();

}
//This actions loads the config choose by the user on Printer Configs
void PrinterConfigs::on_cb_printer_currentTextChanged(const QString &arg1)
{
    loadConfigs(arg1);
}
void PrinterConfigs::on_cb_Extruder_qnt_currentTextChanged(const QString &arg1)
{   this->extrudersInUse = arg1.toInt();
    switch (extrudersInUse)
    {
    case 1:
    {
        ui->bt_extruder2->hide();
        ui->lb_extruderTemp_2->hide();
        ui->lbC2->hide();

        ui->bt_extruder3->hide();
        ui->lb_extruderTemp_3->hide();
        ui->lbC3->hide();

        ui->bt_extruder4->hide();
        ui->lb_extruderTemp_4->hide();
        ui->lbC4->hide();
    }break;
    case 2:
    {   ui->bt_extruder3->hide();
        ui->lb_extruderTemp_3->hide();
        ui->lbC3->hide();

        ui->bt_extruder4->hide();
        ui->lb_extruderTemp_4->hide();
        ui->lbC4->hide();

    }break;
    case 3:
    {
        ui->bt_extruder4->hide();
        ui->lb_extruderTemp_4->hide();
        ui->lbC4->hide();
    }break;

    default:
        break;
    }
}



