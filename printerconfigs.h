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
   void init(QSettings settings);

private:
    Ui::PrinterConfigs *ui;

};

#endif // PRINTERCONFIGS_H
