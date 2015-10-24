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

private:
    Ui::ManualControl *ui;
};

#endif // MANUALCONTROL_H
