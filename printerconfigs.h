#ifndef PRINTERCONFIGS_H
#define PRINTERCONFIGS_H

#include <QWidget>
#include <QSettings>

namespace Ui {
class PrinterConfigs;
}

class PrinterConfigs : public QWidget
{
    Q_OBJECT

public:
    explicit PrinterConfigs(QWidget *parent = 0);
    ~PrinterConfigs();
    void init(QSettings *settings);

private:
    Ui::PrinterConfigs *ui;
    QSettings settings;
    QString extruderTemperature="";
    QString bedTemperature="";
    QString extruderMAXTemp="";
    QString bedMAXTemp="";
    QString areaX="2";
    QString areaY="2";
    QString areaZ="2";
    QString rateMoviment;
    QString extruderSpeed;
    QString extruderRetraction;
    QString extruderQnt;
    QString connectionType;
    QString transmissionRate;
    QString firmwareType;
    QString cacheSize;
    QString connectionPort;
    int resetOnConnect, resetOnEmergency, printLog, qntextruders;
    QString feedZ;
    QString extruderMAXVol;
    //Functions
    void loadConfigs(QString q);

private slots:
    void on_cb_printer_currentTextChanged(const QString &arg1);
    void on_bt_saveConfig_clicked();
    void on_cb_Extruder_qnt_currentTextChanged(const QString &arg1);

};

#endif // PRINTERCONFIGS_H
