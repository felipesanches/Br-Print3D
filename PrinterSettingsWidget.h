#ifndef PRINTERSETTINGSWIDGET_H
#define PRINTERSETTINGSWIDGET_H

#include <QWidget>
#include <PrinterSettings.h>
#include <QSettings>
#include <QInputDialog>

namespace Ui {
class PrinterSettingsWidget;
}

class PrinterSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PrinterSettingsWidget(QWidget *parent = 0);
    ~PrinterSettingsWidget();
    void init(QSettings *settings);
    void setConnectionPort(QStringList s);
    PrinterSettings* getCurrentSettings();

private:
    Ui::PrinterSettingsWidget *ui;
    PrinterSettings *loadConfigs(QString q);
    QSettings *settings;
    int extrudersInUse;

private slots:
    void on_cb_Printer_currentTextChanged(const QString &arg1);
    void on_bt_saveConfig_clicked();
    void on_cb_Extruder_qnt_currentTextChanged(const QString &arg1);

    void disableExtruderQntCB(bool b);
signals:
    void hideExtruders(int e);
    void _extrudersInUse(int e);


};

#endif // PRINTERSETTINGSWIDGET_H
