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
void BrPrint3D::on_bt_killSlicer_clicked()
{

}
