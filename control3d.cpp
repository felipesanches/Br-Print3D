#include "control3d.h"
#include "ui_control3d.h"

Control3D::Control3D(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Control3D)
{
    ui->setupUi(this);
}

Control3D::~Control3D()
{
    delete ui;
}
