#ifndef MANUALCONTROL_H
#define MANUALCONTROL_H

#include <QWidget>

namespace Ui {
class ManualControl;
}

class ManualControl : public QWidget
{
    Q_OBJECT

public:
    explicit ManualControl(QWidget *parent = 0);
    ~ManualControl();
    void init;

private:
    Ui::ManualControl *ui;
    void disableAxisButtons();
    void enableAxisButtons();

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

};

#endif // MANUALCONTROL_H
