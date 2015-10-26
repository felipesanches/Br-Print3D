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
void ManualControl::init()
{
    ui->GCodePreview->setPlainText(tr("No Open File."));

    //Set Values on labels of Manual Control
    ui->lb_value_cooler->setText(QVariant (ui->sl_coolerFan->value()).toString());
    ui->lb_bedTemp->setText(QVariant (ui->sl_bed->value()).toString());
    ui->lb_value_speedfil->setText(QVariant (ui->sl_speedFeedFilament->value()).toString());
    ui->lb_value_vazaofil->setText(QVariant (ui->sl_filamentFlow->value()).toString());
    ui->lb_extruderTemp_0->setText(QVariant (ui->sl_extruder->value()).toString());

}

//This action search for Slic3er manually, if the slic3er isnt installed, the user could user the bin
void ManualControl::on_bt_addSlicer_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this, "Open File",QDir::homePath(),"slic3r");
    ui->cb_Slicer->setItemText(0,"Slic3r");
    settings.setValue("slic3r",filename);
    settings.sync();
    ui->bt_addSlicer->setEnabled(false);
}
//This action start the job of slicing
void ManualControl::on_bt_startSlicer_clicked()
{
    if(ui->cb_Slicer->currentText()=="Slic3r")
    {

    }
    if(ui->cb_Slicer->currentText()=="Cura Engine")
    {

    }
}
//This action kill the job of slicing
void ManualControl::on_bt_killSlicer_clicked()
{

}

/*-----------Printer Actions - Manual Control----*/
/*Home Extruder Functions*/
//This action set Home X Axis
void ManualControl::on_bt_home_X_clicked()
{
    this->printer_object->homeAxis('X');

}
//This action set Home Y Axis
void ManualControl::on_bt_home_Y_clicked()
{
    this->printer_object->homeAxis('Y');

}
//This action set home Z Axis
void ManualControl::on_bt_home_Z_clicked()
{
    this->printer_object->homeAxis('Z');

}
//This action set home XYZ Axis
void ManualControl::on_bt_home_XYZ_clicked()
{
    this->printer_object->homeAllAxis();

}
/*Filament Retract*/
//This action retract the filament
void ManualControl::on_bt_filamentoRetract_clicked()
{
    //this->printer_object->extruderControl(0.1,0.1);
}
//This action expulse the filament at 1x
void ManualControl::on_bt_filamentoOneSpeed_clicked()
{


}
//This action expulse the filament at 2x
void ManualControl::on_bt_filamentoTwoSpeed_clicked()
{


}

/*Sliders Values Set*/
//This action set the value of velocity of feed of filament to slider and printer
void ManualControl::on_tb_speedFeedFilament_textChanged(const QString &arg1)
{
    ui->sl_speedFeedFilament->setValue(arg1.toInt());
}
//This action set the value of filament Flow to slider and printer
void ManualControl::on_tb_filamentFlow_textChanged(const QString &arg1)
{
    ui->sl_speedFeedFilament->setValue(arg1.toInt());
}
//This action set the value of cooler fan to slider and printer
void ManualControl::on_tb_coolerfan_textChanged(const QString &arg1)
{
    ui->sl_coolerFan->setValue(arg1.toInt());
}

/*Heating actions*/
//This action start heating the bed of the printer
void ManualControl::on_bt_Bed_clicked(bool checked)
{
    if(checked==true)
    {       float tmp = ui->tb_BedTempMC->text().toFloat();
            this->printer_object->setBedTemp(tmp);
    }
    else
    {   ui->bt_Bed->setStyleSheet("");
       this->printer_object->setBedTemp(0);
    }
}
//This action start heating the extruder(s)
void ManualControl::on_bt_extruderTemp_clicked(bool checked)
{
    if(checked==true)
    {
        for(int i=1;i<=extrudersInUse;i++)
           this->printer_object->setExtrTemp(i-1,ui->tb_ExtruderTempMC->text().toFloat());

    }
    if(checked==false)
    {
        ui->bt_extruderTemp->setStyleSheet("");
        for(int i=1;i<=extrudersInUse;i++)
        {   this->printer_object->setExtrTemp(i-1,0);
            switch (i)
            {
            case 1:
                ui->bt_extruder1->setStyleSheet("");
            break;
            case 2:
                ui->bt_extruder2->setStyleSheet("");
            break;
            case 3:
                ui->bt_extruder3->setStyleSheet("");
            break;
            case 4:
                ui->bt_extruder4->setStyleSheet("");
            break;
            default:
                break;
            }
        }
    }
}
//This function disable some buttons from Manual Control for safety
void ManualControl::disableAxisButtons()
{
    ui->bt_home_X->setEnabled(false);
    ui->bt_home_Y->setEnabled(false);
    ui->bt_home_Z->setEnabled(false);
    ui->bt_home_XYZ->setEnabled(false);
    ui->bt_up_Y->setEnabled(false);
    ui->bt_down_Y->setEnabled(false);
    ui->bt_left_X->setEnabled(false);
    ui->bt_right_X->setEnabled(false);
    ui->bt_down_Z->setEnabled(false);
    ui->bt_up_Z->setEnabled(false);
    ui->bt_filamentoOneSpeed->setEnabled(false);
    ui->bt_filamentoRetract->setEnabled(false);
    ui->bt_filamentoTwoSpeed->setEnabled(false);
}
//This function enable some buttons from Manual Control
void ManualControl::enableAxisButtons()
{
    ui->bt_home_X->setEnabled(true);
    ui->bt_home_Y->setEnabled(true);
    ui->bt_home_Z->setEnabled(true);
    ui->bt_home_XYZ->setEnabled(true);
    ui->bt_up_Y->setEnabled(true);
    ui->bt_down_Y->setEnabled(true);
    ui->bt_left_X->setEnabled(true);
    ui->bt_right_X->setEnabled(true);
    ui->bt_down_Z->setEnabled(true);
    ui->bt_up_Z->setEnabled(true);
    ui->bt_filamentoOneSpeed->setEnabled(true);
    ui->bt_filamentoRetract->setEnabled(true);
    ui->bt_filamentoTwoSpeed->setEnabled(true);
}
//This function blocks other buttons for security and ensuring that the slider of extruder temperature is belonging to extruder 1
void ManualControl::on_bt_extruder1_clicked(bool checked)
{
    if(checked==true)
    {
        ui->bt_extruder2->setEnabled(false);
        ui->bt_extruder3->setEnabled(false);
        ui->bt_extruder4->setEnabled(false);
        ui->bt_extruderTemp->setText("1");
    }
    else
    {
        ui->bt_extruder2->setEnabled(true);
        ui->bt_extruder3->setEnabled(true);
        ui->bt_extruder4->setEnabled(true);
    }
}
//This function blocks other buttons for security and ensuring that the slider of extruder temperature is belonging to extruder 2
void ManualControl::on_bt_extruder2_clicked(bool checked)
{
    if(checked==true)
    {
        ui->bt_extruder1->setEnabled(false);
        ui->bt_extruder3->setEnabled(false);
        ui->bt_extruder4->setEnabled(false);
        ui->bt_extruderTemp->setText("2");
    }
    else
    {
        ui->bt_extruder1->setEnabled(true);
        ui->bt_extruder3->setEnabled(true);
        ui->bt_extruder4->setEnabled(true);
    }
}
//This function blocks other buttons for security and ensuring that the slider of extruder temperature is belonging to extruder 3
void ManualControl::on_bt_extruder3_clicked(bool checked)
{
    if(checked==true)
    {
        ui->bt_extruder2->setEnabled(false);
        ui->bt_extruder1->setEnabled(false);
        ui->bt_extruder4->setEnabled(false);
        ui->bt_extruderTemp->setText("3");
    }
    else
    {
        ui->bt_extruder2->setEnabled(true);
        ui->bt_extruder1->setEnabled(true);
        ui->bt_extruder4->setEnabled(true);
    }
}
//This function blocks other buttons for security and ensuring that the slider of extruder temperature is belonging to extruder 4
void ManualControl::on_bt_extruder4_clicked(bool checked)
{
    if(checked==true)
    {
        ui->bt_extruder2->setEnabled(false);
        ui->bt_extruder3->setEnabled(false);
        ui->bt_extruder1->setEnabled(false);
        ui->bt_extruderTemp->setText("4");
    }
    else
    {
        ui->bt_extruder2->setEnabled(true);
        ui->bt_extruder3->setEnabled(true);
        ui->bt_extruder1->setEnabled(true);
    }
}
//This Action update the temperature of the bed if the print job is on
void ManualControl::on_tb_BedTempMC_textEdited(const QString &arg1)
{   if(ui->bt_play->isChecked() && ui->bt_Bed->isChecked())
        this->printer_object->setBedTemp(arg1.toInt());
}
//This Action update the temperature of the extruders if the print job is on
void ManualControl::on_tb_ExtruderTempMC_textEdited(const QString &arg1)
{   if(ui->bt_play->isChecked() && ui->bt_extruderTemp->isChecked() )
    for(int i=1;i<=extrudersInUse;i++)
        this->printer_object->setExtrTemp(i-1,arg1.toInt());
}
//This Action set the X axis to new position on right
void ManualControl::on_bt_right_X_clicked()
{   double pos = this->printer_object->getCurrentXPos();
    pos+=ui->cb_valuePosXY->currentText().toFloat();
    this->printer_object->moveAxisToPos('X',pos);
}
//This Action set the X axis to new position on left
void ManualControl::on_bt_left_X_clicked()
{   QMessageBox msg;
    msg.setText("Invalid Position!");
    msg.setIcon(QMessageBox::Warning);
    double pos = this->printer_object->getCurrentXPos();
    pos-=ui->cb_valuePosXY->currentText().toFloat();
    if(pos<=0)
        msg.exec();
    else
        this->printer_object->moveAxisToPos('X',pos);
}
//This Action set the Y axis to new position on up
void ManualControl::on_bt_up_Y_clicked()
{
    double pos = this->printer_object->getCurrentYPos();
    pos+=ui->cb_valuePosXY->currentText().toFloat();
    this->printer_object->moveAxisToPos('Y',pos);
}
//This Action set the Y axis to new position on down
void ManualControl::on_bt_down_Y_clicked()
{   QMessageBox msg;
    msg.setText("Invalid Position!");
    msg.setIcon(QMessageBox::Warning);
    double pos = this->printer_object->getCurrentYPos();
    pos-=ui->cb_valuePosXY->currentText().toFloat();
    if(pos<=0)
        msg.exec();
    else
        this->printer_object->moveAxisToPos('Y',pos);

}
//This Action set the Z axis to new position on up
void ManualControl::on_bt_up_Z_clicked()
{
    double pos = this->printer_object->getCurrentZPos();
    pos+=ui->cb_valuePosXY->currentText().toFloat();
    this->printer_object->moveAxisToPos('Z',pos);

}
//This Action set the Z axis to new position on down
void ManualControl::on_bt_down_Z_clicked()
{   QMessageBox msg;
    msg.setText("Invalid Position!");
    msg.setIcon(QMessageBox::Warning);
    double pos = this->printer_object->getCurrentZPos();
    pos-=ui->cb_valuePosXY->currentText().toFloat();
    if(pos<=0)
        msg.exec();
    else
        this->printer_object->moveAxisToPos('Z',pos);
}
