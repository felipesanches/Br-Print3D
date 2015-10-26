#include "loading.h"
#include "ui_loading.h"
#include "BrPrint3D.h"

Loading::Loading(QWidget *parent) :
    QDialog(parent), ui(new Ui::Loading)
{

    ui->setupUi(this);

}

Loading::~Loading()
{
    delete ui;
}

void Loading::on_pushButton_clicked()
{
    this->close();
}
