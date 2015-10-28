#include "PrinterSettingsWidget.h"
#include "ui_PrinterSettingsWidget.h"

PrinterSettingsWidget::PrinterSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrinterSettingsWidget)
{
    ui->setupUi(this);
}

PrinterSettingsWidget::~PrinterSettingsWidget()
{
    delete ui;
}

void PrinterSettingsWidget::init(QSettings *settings)
{   this->settings = settings;
    //Load the previous configs if them exists
    QStringList groups;
    settings->beginGroup("Printer_Configs");
    groups = settings->childGroups();
    settings->endGroup();
    ui->cb_Printer->addItems(groups);
    if(!groups.isEmpty())
    {   //Criar init printer configs
        QString a = ui->cb_Printer->currentText();
        PrinterSettings p = loadConfigs(a);
        //Connection Tab
        ui->cb_Connection_Type->setCurrentText(p.connectionType);
        ui->cb_Transmition_Rate->setCurrentText(p.transmissionRate);
        ui->cb_Firmware->setCurrentText(p.firmwareType);
        ui->cb_Cache_Size->setCurrentText(p.cacheSize);

        //Resets
        ui->ck_ResetonConnect->setChecked(p.resetOnConnect);
        ui->ck_ResetonEmergency->setChecked(p.resetOnEmergency);
        ui->ck_PrintLog->setChecked(p.printLog);

        //Printer Tab
        ui->tb_RateMoviment->setText(p.rateMoviment);
        ui->tb_FeedZ->setText(p.feedZ);
        ui->tb_ExtSpeedmm->setText(p.extruderSpeedMM);
        ui->tb_ExtSpeedSec->setText(p.extruderSpeedS);
        ui->tb_ExtMaxVol->setText(p.extruderMAXVol);
        ui->tb_RetractionSpeed->setText(p.extruderRetraction);
        ui->tb_BedTemp->setText(p.bedTemperature);
        ui->tb_ExtTemperature->setText(p.extruderTemperature);
        ui->tb_AreaPrintX->setText(p.areaX);
        ui->tb_AreaPrintY->setText(p.areaY);
        ui->tb_AreaPrintZ->setText(p.areaZ);

        //Extruder Tab
        ui->cb_ExtruderQnt->setCurrentText(p.extruderQnt);
        ui->tb_ExtMaxTemp->setText(p.extruderMAXTemp);
        ui->tb_BedMaxTemp->setText(p.bedMAXTemp);
    }

}
//This action save the configs insert by the user on Printer Configs in Ini File
void PrinterSettingsWidget::on_bt_SaveConfig_clicked() //Save actual configs
{   bool ok;
    QString name = QInputDialog::getText(this, tr("Insert the name of config: "),tr("Name:"),QLineEdit::Normal,"ex.: Graber1",&ok);
    this->settings->beginGroup("Printer_Configs");
    if(ok && !name.isEmpty())
    {   PrinterSettings p = this->getCurrentSettings();
        this->settings->beginGroup(name);
        //Conexao
        this->settings->setValue("Firmware",p.firmwareType);
        this->settings->setValue("ResetOnConnect",p.resetOnConnect);
        this->settings->setValue("ResetonEmergency",p.resetOnEmergency);
        this->settings->setValue("CacheSize",p.cacheSize);
        this->settings->setValue("TransmissionRate",p.transmissionRate);
        this->settings->setValue("PrinterLog",p.printLog);
        //Impressora
        this->settings->setValue("RateMoviment",p.rateMoviment);
        this->settings->setValue("FeedZ",p.feedZ);
        this->settings->setValue("ExtruderSpeedMM",p.extruderSpeedMM);
        this->settings->setValue("ExtruderSpeedSec",p.extruderSpeedS);
        this->settings->setValue("ExtruderRetraction",p.extruderRetraction);
        this->settings->setValue("BedTemperature",p.bedTemperature);
        this->settings->setValue("ExtruderTemperature",p.extruderTemperature);
        this->settings->setValue("AreaX",p.areaX);
        this->settings->setValue("AreaY",p.areaY);
        this->settings->setValue("AreaZ",p.areaZ);
        //Extrusor
        this->settings->setValue("ExtruderQnt",p.extrudersInUse);
        this->settings->setValue("ExtruderMaxTemp",p.extruderMAXTemp);
        this->settings->setValue("BedMaxTemp",p.bedMAXTemp);
        this->settings->setValue("VolumeMax",p.extruderMAXVol);
        this->settings->endGroup();

    }
    this->settings->endGroup();
    QStringList groups;
    this->settings->beginGroup("Printer_Configs");
    groups = this->settings->childGroups();
    this->settings->endGroup();
    ui->cb_Printer->clear();
    ui->cb_Printer->addItems(groups);
}

PrinterSettings PrinterSettingsWidget::loadConfigs(QString q)
{
        settings->beginGroup("Printer_Configs");
        settings->beginGroup(q);
        PrinterSettings p;
        //Connection
       p.connectionType = settings->value("ConnectionType","USB").toString();
       p.transmissionRate = settings->value("TransmissionRate","115200").toString();
       p.firmwareType = settings->value("Firmware","Repetier").toString();
       p.cacheSize = settings->value("CacheSize","127").toString();
       p.resetOnConnect = settings->value("ResetOnConnect",2).toInt();
       p.resetOnEmergency = settings->value("ResetonEmergency",0).toInt();
       p.printLog = settings->value("PrinterLog",0).toInt();

        //Printer
       p.rateMoviment = settings->value("RateMoviment",0).toString();
       p.feedZ = settings->value("FeedZ",0).toString();
       p.extruderSpeedMM = settings->value("ExtruderSpeedMM",0).toString();
       p.extruderSpeedS = settings->value("ExtruderSpeedSec",0).toString();
       p.extruderRetraction = settings->value("ExtruderRetraction",0).toString();
       p.extruderTemperature = settings->value("ExtruderTemperature",210).toString();
       p.bedTemperature = settings->value("BedTemperature",110).toString();
       p.areaX = settings->value("AreaX",0).toString();
       p.areaY = settings->value("AreaY",0).toString();
       p.areaZ = settings->value("AreaZ",0).toString();

        //Extruder
       p.extruderQnt = settings->value("ExtruderQnt",1).toString();
       p.extruderMAXTemp = settings->value("ExtruderMaxTemp",230).toString();
       p.bedMAXTemp = settings->value("BedMaxTemp",120).toString();
       p.extruderMAXVol = settings->value("VolumeMax",0).toString();
        settings->endGroup();
        settings->endGroup();
        return p;

}
//This actions loads the config choose by the user on Printer Configs
void PrinterSettingsWidget::on_cb_Printer_currentTextChanged(const QString &arg1)
{
    loadConfigs(arg1);
}
PrinterSettings PrinterSettingsWidget::getCurrentSettings()
{
    PrinterSettings p;
    p.connectionType = ui->cb_Connection_Type->currentText();
    p.connectionPort = ui->cb_Connection_Port->currentText();
    p.transmissionRate = ui->cb_Transmition_Rate->currentText();
    p.firmwareType = ui->cb_Firmware->currentText();
    p.cacheSize = ui->cb_Cache_Size->currentText();
    p.resetOnConnect = ui->ck_ResetonConnect->isChecked();
    p.resetOnEmergency = ui->ck_ResetonEmergency->isChecked();
    p.printLog = ui->ck_PrintLog->isChecked();
    p.rateMoviment = ui->tb_RateMoviment->text();
    p.feedZ = ui->tb_FeedZ->text();
    p.extruderSpeedMM = ui->tb_ExtSpeedmm->text();
    p.extruderSpeedS = ui->tb_ExtSpeedSec->text();
    p.extruderRetraction = ui->tb_RetractionSpeed->text();
    p.extruderTemperature = ui->tb_ExtTemperature->text();
    p.bedTemperature = ui->tb_BedTemp->text();
    p.areaX = ui->tb_AreaPrintX->text();
    p.areaY = ui->tb_AreaPrintY->text();
    p.areaZ = ui->tb_AreaPrintZ->text();
    p.extrudersInUse = ui->cb_ExtruderQnt->currentText().toInt();
    p.extruderMAXTemp = ui->tb_ExtMaxTemp->text();
    p.extruderMAXVol = ui->tb_ExtMaxVol->text();
    p.bedMAXTemp = ui->tb_BedMaxTemp->text();
    return p;


}
void PrinterSettingsWidget::setConnectionPort(QStringList p)
{
    ui->cb_Connection_Port->addItems(p);
}
void PrinterSettingsWidget::disableExtrudersQntCB(bool b)
{
    ui->cb_ExtruderQnt->setDisabled(true);
}

void PrinterSettingsWidget::on_cb_ExtruderQnt_currentTextChanged(const QString &arg1)
{
        this->extrudersInUse = arg1.toInt();
        emit hideExtruders(this->extrudersInUse);
        emit _extrudersInUse(this->extrudersInUse);

}
