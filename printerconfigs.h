#ifndef PRINTERCONFIGS_H
#define PRINTERCONFIGS_H

#include <QWidget>

namespace Ui {
class PrinterConfigs;
}

class PrinterConfigs : public QWidget
{
    Q_OBJECT

public:
    explicit PrinterConfigs(QWidget *parent = 0);
    ~PrinterConfigs();

private:
    Ui::PrinterConfigs *ui;
};

#endif // PRINTERCONFIGS_H
