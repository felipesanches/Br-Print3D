#ifndef PRINTERSETTINGSWIDGET_H
#define PRINTERSETTINGSWIDGET_H

#include <QWidget>
#include <PrinterSettings.h>
#include <QSettings>

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

private:
    Ui::PrinterSettingsWidget *ui;
    PrinterSettings loadConfigs(QString q);
    QSettings settings;
    PrinterSettings getCurrentSettings();
private slots:
    void on_cb_Printer_currentTextChanged(const QString &arg1);
    void on_bt_saveConfig_clicked();
    void on_cb_Extruder_qnt_currentTextChanged(const QString &arg1);
    int extrudersInUse;
signals:
    void hideExtruders(int e);



};

#endif // PRINTERSETTINGSWIDGET_H
