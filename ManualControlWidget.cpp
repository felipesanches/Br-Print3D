#include "ManualControlWidget.h"
#include "ui_ManualControlWidget.h"

ManualControlWidget::ManualControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManualControlWidget)
{
    ui->setupUi(this);
}

ManualControlWidget::~ManualControlWidget()
{
    delete ui;
}

void ManualControlWidget::init()
{
    ui->GCodePreview->setPlainText(tr("No Open File."));

    //Set Values on labels of Manual Control
    ui->lb_value_cooler->setText(QVariant (ui->sl_coolerFan->value()).toString());
    ui->lb_bedTemp->setText(QVariant (ui->sl_bed->value()).toString());
    ui->lb_value_speedfil->setText(QVariant (ui->sl_speedFeedFilament->value()).toString());
    ui->lb_value_vazaofil->setText(QVariant (ui->sl_filamentFlow->value()).toString());
    ui->lb_extruderTemp_0->setText(QVariant (ui->sl_extruder->value()).toString());

    //If slic3er exists in Ini file, load path, else locate
    pathslicer=QVariant (settings.value("slic3r")).toString();
    if(pathslicer.isEmpty())
        locate_Slicer();
    else
    {   ui->cb_Slicer->addItem("Slic3r");
        ui->bt_addSlicer->setEnabled(false);
    }

    //If cura exists in Ini file, load path, else locate
    pathcura=QVariant (settings.value("cura")).toString();
    if(pathcura.isEmpty())
        locate_Cura();
    else
        ui->cb_Slicer->addItem("Cura Engine");

}

//This action search for Slic3er manually, if the slic3er isnt installed, the user could user the bin
void ManualControlWidget::on_bt_addSlicer_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this, "Open File",QDir::homePath(),"slic3r");
    ui->cb_Slicer->setItemText(0,"Slic3r");
    settings.setValue("slic3r",filename);
    settings.sync();
    ui->bt_addSlicer->setEnabled(false);
}
//This action start the job of slicing
void ManualControlWidget::on_bt_startSlicer_clicked()
{
    if(ui->cb_Slicer->currentText()=="Slic3r")
    {

    }
    if(ui->cb_Slicer->currentText()=="Cura Engine")
    {

    }
}
//This action kill the job of slicing
void ManualControlWidget::on_bt_killSlicer_clicked()
{

}

/*-----------Printer Actions - Manual Control----*/
/*Home Extruder Functions*/
//This action set Home X Axis
void ManualControlWidget::on_bt_home_X_clicked()
{
    this->printer_object->homeAxis('X');

}
//This action set Home Y Axis
void ManualControlWidget::on_bt_home_Y_clicked()
{
    this->printer_object->homeAxis('Y');

}
//This action set home Z Axis
void ManualControlWidget::on_bt_home_Z_clicked()
{
    this->printer_object->homeAxis('Z');

}
//This action set home XYZ Axis
void ManualControlWidget::on_bt_home_XYZ_clicked()
{
    this->printer_object->homeAllAxis();

}
/*Filament Retract*/
//This action retract the filament
void ManualControlWidget::on_bt_filamentoRetract_clicked()
{
    //this->printer_object->extruderControl(0.1,0.1);
}
//This action expulse the filament at 1x
void ManualControlWidget::on_bt_filamentoOneSpeed_clicked()
{


}
//This action expulse the filament at 2x
void ManualControlWidget::on_bt_filamentoTwoSpeed_clicked()
{


}

/*Sliders Values Set*/
//This action set the value of velocity of feed of filament to slider and printer
void ManualControlWidget::on_tb_speedFeedFilament_textChanged(const QString &arg1)
{
    ui->sl_speedFeedFilament->setValue(arg1.toInt());
}
//This action set the value of filament Flow to slider and printer
void ManualControlWidget::on_tb_filamentFlow_textChanged(const QString &arg1)
{
    ui->sl_speedFeedFilament->setValue(arg1.toInt());
}
//This action set the value of cooler fan to slider and printer
void ManualControlWidget::on_tb_coolerfan_textChanged(const QString &arg1)
{
    ui->sl_coolerFan->setValue(arg1.toInt());
}

/*Heating actions*/
//This action start heating the bed of the printer
void ManualControlWidget::on_bt_Bed_clicked(bool checked)
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
void ManualControlWidget::on_bt_extruderTemp_clicked(bool checked)
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
void ManualControlWidget::disableAxisButtons()
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
void ManualControlWidget::enableAxisButtons()
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
void ManualControlWidget::on_bt_extruder1_clicked(bool checked)
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
void ManualControlWidget::on_bt_extruder2_clicked(bool checked)
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
void ManualControlWidget::on_bt_extruder3_clicked(bool checked)
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
void ManualControlWidget::on_bt_extruder4_clicked(bool checked)
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
void ManualControlWidget::on_tb_BedTempMC_textEdited(const QString &arg1)
{   if(ui->bt_play->isChecked() && ui->bt_Bed->isChecked())
        this->printer_object->setBedTemp(arg1.toInt());
}
//This Action update the temperature of the extruders if the print job is on
void ManualControlWidget::on_tb_ExtruderTempMC_textEdited(const QString &arg1)
{   if(ui->bt_play->isChecked() && ui->bt_extruderTemp->isChecked() )
    for(int i=1;i<=extrudersInUse;i++)
        this->printer_object->setExtrTemp(i-1,arg1.toInt());
}
//This Action set the X axis to new position on right
void ManualControlWidget::on_bt_right_X_clicked()
{   double pos = this->printer_object->getCurrentXPos();
    pos+=ui->cb_valuePosXY->currentText().toFloat();
    this->printer_object->moveAxisToPos('X',pos);
}
//This Action set the X axis to new position on left
void ManualControlWidget::on_bt_left_X_clicked()
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
void ManualControlWidget::on_bt_up_Y_clicked()
{
    double pos = this->printer_object->getCurrentYPos();
    pos+=ui->cb_valuePosXY->currentText().toFloat();
    this->printer_object->moveAxisToPos('Y',pos);
}
//This Action set the Y axis to new position on down
void ManualControlWidget::on_bt_down_Y_clicked()
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
void ManualControlWidget::on_bt_up_Z_clicked()
{
    double pos = this->printer_object->getCurrentZPos();
    pos+=ui->cb_valuePosXY->currentText().toFloat();
    this->printer_object->moveAxisToPos('Z',pos);

}
//This Action set the Z axis to new position on down
void ManualControlWidget::on_bt_down_Z_clicked()
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
void ManualControlWidget::getPrinterObject(Repetier *printer_object)
{
    this->printer_object = printer_object;
}
void ManualControlWidget::setInitialMarks()
{
    this->qntExtruders = this->printer_object->getNoOfExtruders();


   double x,y,z;
   char resp[51];

   x = this->printer_object->getCurrentXPos();
   y = this->printer_object->getCurrentYPos();
   z = this->printer_object->getCurrentZPos();

   sprintf(resp, "%.3lf", x);
   QString xx = QString::fromUtf8(resp);
   ui->tb_posicaoeixoX->setText(xx);
   sprintf(resp, "%.3lf", y);
   QString yy = QString::fromUtf8(resp);
   ui->tb_posicaoeixoY->setText(yy);
   sprintf(resp, "%.3lf", z);
   QString zz = QString::fromUtf8(resp);
   ui->tb_posicaoeixoZ->setText(zz);

   //Create the tread for read temperatures and position
   this->temp = new ThreadRoutine(this->printer_object,&extrudersInUse);
   this->temp->start();
   //Connect some signals
   connect(temp,SIGNAL(updateTemp(double*,double)),this,SLOT(updateTemp(double*,double)));
   connect(temp,SIGNAL(updatePos(double,double,double)),this,SLOT(updatePos(double,double,double)));
}

//This slot update on UI the value of Temperatures of the Bed and Extruders
void ManualControlWidget::updateTemp(double *temp_Extruders, double tempBed)
{   //This function update the printer temperatures on the screen
    float temp_Bed = tempBed;
    //Change bed temperatures
    ui->sl_bed->setValue(temp_Bed);
    ui->lb_bedTemp->setText(QVariant(temp_Bed).toString());
    //Update Color Status
    if(ui->bt_Bed->isChecked())
    {
        if(ui->sl_bed->value()>=ui->tb_BedTempMC->text().toInt())
            ui->bt_Bed->setStyleSheet("background-color:red;");
        else
            ui->bt_Bed->setStyleSheet("background-color:yellow;");
     }
     //If the printer is using one extruder, the slider will belongs all the time to extruder 1
     if(extrudersInUse==1)
     {
        ui->sl_extruder->setValue(temp_Extruders[0]);//Set temperature on slider
        ui->lb_extruderTemp_0->setText(QVariant(temp_Extruders[0]).toString());//Set Label of slider
        ui->lb_extruderTemp_1->setText(QVariant(temp_Extruders[0]).toString());//Set label on Ext 1
        //Change color status
        if(ui->bt_extruderTemp->isChecked())
        {   if(ui->lb_extruderTemp_1->text().toFloat()>=ui->tb_ExtruderTempMC->text().toInt())
            {    ui->bt_extruder1->setStyleSheet("background-color:red;");
                 ui->bt_extruderTemp->setStyleSheet("background-color:red;");
            }
            else
            {    ui->bt_extruder1->setStyleSheet("background-color:yellow;");
                 ui->bt_extruderTemp->setStyleSheet("background-color:yellow;");
            }
        }

     }
     else
     {  //Change extruders temp
        ui->bt_extruderTemp->setStyleSheet("background-color:green;");
        for(int i=1;i<=extrudersInUse;i++)
        {
            switch (i)
            {
                case 1:
                {   if(ui->bt_extruder1->isChecked())//Slider belongs to extruder 1
                    {
                        ui->sl_extruder->setValue(temp_Extruders[i-1]); //Set Slider value
                        ui->lb_extruderTemp_0->setText(QVariant(temp_Extruders[i-1]).toString());//Set Label of slider
                    }
                    //Refresh Color Status
                    if(ui->bt_extruderTemp->isChecked())
                    {   if(ui->lb_extruderTemp_1->text().toFloat()>=ui->tb_ExtruderTempMC->text().toInt() && ui->bt_extruderTemp->isChecked())
                            ui->bt_extruder1->setStyleSheet("background-color:red;");
                        else
                            ui->bt_extruder1->setStyleSheet("background-color:yellow;");
                    }
                    ui->lb_extruderTemp_1->setText(QVariant(temp_Extruders[i-1]).toString());//Set label extruder value

                }break;
                case 2:
                {   if(ui->bt_extruder2->isChecked())//Slider belongs to extruder two
                    {   ui->sl_extruder->setValue(temp_Extruders[i-1]);
                        ui->lb_extruderTemp_0->setText(QVariant(temp_Extruders[i-1]).toString());//Set Label of slider
                    }
                   //Refresh Color Status
                   if(ui->bt_extruderTemp->isChecked())
                   {    if(ui->lb_extruderTemp_2->text().toFloat()>=ui->tb_ExtruderTempMC->text().toInt() && ui->bt_extruderTemp->isChecked())//Refresh Color Status
                            ui->bt_extruder2->setStyleSheet("background-color:red;");
                        else
                            ui->bt_extruder2->setStyleSheet("background-color:yellow;");
                   }
                   ui->lb_extruderTemp_2->setText(QVariant(temp_Extruders[i-1]).toString());
                }break;
                case 3:
                {  if(ui->bt_extruder3->isChecked())//Slider belongs to extruder two
                   {   ui->sl_extruder->setValue(temp_Extruders[i-1]);
                       ui->lb_extruderTemp_0->setText(QVariant(temp_Extruders[i-1]).toString());//Set Label of slider
                   }

                    //Refresh Color Status
                   if(ui->bt_extruderTemp->isChecked())
                   {
                       if(ui->lb_extruderTemp_3->text().toFloat()>=ui->tb_ExtruderTempMC->text().toInt() && ui->bt_extruderTemp->isChecked())//Refresh Color Status
                            ui->bt_extruder3->setStyleSheet("background-color:red;");
                        else
                            ui->bt_extruder3->setStyleSheet("background-color:yellow;");
                   }
                    ui->lb_extruderTemp_3->setText(QVariant(temp_Extruders[i-1]).toString());
                }break;
                case 4:
                {  if(ui->bt_extruder4->isChecked())//Slider belongs to extruder two
                   {   ui->sl_extruder->setValue(temp_Extruders[i-1]);
                       ui->lb_extruderTemp_0->setText(QVariant(temp_Extruders[i-1]).toString());//Set Label of slider
                   }
                   //Change Color Status
                   if(ui->bt_extruderTemp->isChecked())
                   {
                        if(ui->lb_extruderTemp_4->text().toFloat()>=ui->tb_ExtruderTempMC->text().toInt() && ui->bt_extruderTemp->isChecked())//Refresh Color Status
                            ui->bt_extruder4->setStyleSheet("background-color:red;");
                        else
                            ui->bt_extruder4->setStyleSheet("background-color:yellow;");
                   }
                    ui->lb_extruderTemp_4->setText(QVariant(temp_Extruders[i-1]).toString());
                }break;
                default:
                    break;
                }
            }
}
}
//This slot update on UI the position of the Extruder
void ManualControlWidget::updatePos(double posX, double posY, double posZ)
{   //This function update the extruder position on the screen
    char resp[51];
    sprintf(resp, "%.3lf", posX);
    QString xx = QString::fromUtf8(resp);
    sprintf(resp, "%.3lf", posY);
    QString yy = QString::fromUtf8(resp);
    sprintf(resp, "%.3lf", posZ);
    QString zz = QString::fromUtf8(resp);
    ui->tb_posicaoeixoX->setText(xx);
    ui->tb_posicaoeixoY->setText(yy);
    ui->tb_posicaoeixoZ->setText(zz);

}
void ManualControlWidget::stopThreadRoutine()
{
    this->temp->setLoop(true);
    this->temp->wait(2000);
    this->temp->quit();
    this->temp->~ThreadRoutine();
}

void ManualControlWidget::setBedStatus(bool b)
{
    ui->bt_Bed->setChecked(b);
    if(b==false)
        ui->bt_Bed->setStyleSheet("");

}
void ManualControlWidget::setExtruderStatus(bool b)
{
    ui->bt_extruderTemp->setChecked(b);
    if(b==false)
        ui->bt_extruderTemp->setStyleSheet("");
}
void ManualControlWidget::hideExtruders(int e)
{
    switch (e)
    {
    case 1:
    {   ui->bt_extruder2->hide();
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

//This function locate the Sli3er program and save on Ini file
void ManualControlWidget::locate_Slicer()
{   QMessageBox msg;
    garbage=std::system("whereis slic3r > slic3r.txt");
    std::ifstream slicer("slic3r.txt");
    char path[201];
    if(!slicer)
    {
        msg.setText("Bin Slic3r could not be open!");
        msg.exec();
    }
    else
    {   if(!slicer.eof())
        {   slicer.getline(path,sizeof(path));//Lê a linha do arquivo
            if(path[7]=='\0')
            {
               msg.setText("Slic3r not found! To search click on add Slicer on tab Slicer!");
               ui->cb_Slicer->addItem("Slic3er (Not Found)");
               //msg.exec();
            }
            else
            {   for(int i=8;path[i]!=' ';i++)
                {
                    pathslicer+=path[i];
                }
                ui->cb_Slicer->addItem("Slic3r");
                settings.setValue("slic3r",pathslicer);//Save the path on ini file
                settings.sync();//Atualiza ini
            }
        }
    }
}
//This function locate the Cura program and save on Ini file
void ManualControlWidget::locate_Cura()
{   QMessageBox msg;
    garbage=std::system("whereis cura > cura.txt");
    std::ifstream cura("cura.txt");
    char path[201];
    if(!cura)
    {
        msg.setText("Bin Cura could not be open!");
        msg.exec();
    }
    else
    {
        if(!cura.eof())
        {
            cura.getline(path,sizeof(path));//read line of the file
            if(path[5]=='\0')
            {
                ui->cb_Slicer->addItem("Cura Engine (Not Found)");
            }
            else
            {
                for(int j=6;path[j]!=' ';j++)
                {
                    pathcura+=path[j];
                }
               ui->cb_Slicer->addItem("Cura Engine");
               settings.setValue("cura",pathcura);
               settings.sync();
            }
        }
    }
}
