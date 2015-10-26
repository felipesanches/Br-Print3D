#ifndef MANUALCONTROLWIDGET_H
#define MANUALCONTROLWIDGET_H

#include <QWidget>
#include <KI/Repetier.h>
#include <threadRotine.h>

namespace Ui {
class ManualControlWidget;
}

class ManualControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ManualControlWidget(QWidget *parent = 0);
    ~ManualControlWidget();

private:
    Ui::ManualControlWidget *ui;
    void disableAxisButtons();
    void enableAxisButtons();
    Repetier *printer_object;
    ThreadRoutine *temp=NULL;
    int qntExtruders;
    void stopThreadRoutine();
    void setBedStatus(bool b);
    void setExtruderStatus(bool b);

private slots:
    void on_bt_extruder1_clicked(bool checked);
    void on_bt_extruder2_clicked(bool checked);
    void on_bt_extruder3_clicked(bool checked);
    void on_bt_extruder4_clicked(bool checked);
    void on_tb_filamentFlow_textChanged(const QString &arg1);
    void on_tb_speedFeedFilament_textChanged(const QString &arg1);
    void on_tb_coolerfan_textChanged(const QString &arg1);
    void on_bt_Bed_clicked(bool checked);
    void on_tb_BedTempMC_textEdited(const QString &arg1);
    void on_tb_ExtruderTempMC_textEdited(const QString &arg1);
    void on_bt_up_Y_clicked();
    void on_bt_left_X_clicked();
    void on_bt_down_Y_clicked();
    void on_bt_right_X_clicked();
    void on_bt_up_Z_clicked();
    void on_bt_down_Z_clicked();
    void on_bt_filamentoRetract_clicked();
    void on_bt_filamentoOneSpeed_clicked();
    void on_bt_filamentoTwoSpeed_clicked();
    void on_bt_home_X_clicked();
    void on_bt_home_Y_clicked();
    void on_bt_home_Z_clicked();
    void on_bt_home_XYZ_clicked();
    void on_bt_extruderTemp_clicked(bool checked);
    void on_bt_addSlicer_clicked();
    void getPrinterObject(Repetier *printer_object);

    void updateTemp(double *temp_Extruders, double tempTable);
    void updateExt(double posX, double posY, double posZ);
    void hideExtruders(int e);
};

#endif // MANUALCONTROLWIDGET_H
