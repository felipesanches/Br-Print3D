#ifndef CONTROL3D_H
#define CONTROL3D_H

#include <QWidget>

namespace Ui {
class Control3D;
}

class Control3D : public QWidget
{
    Q_OBJECT

public:
    explicit Control3D(QWidget *parent = 0);
    ~Control3D();

private:
    Ui::Control3D *ui;
};

#endif // CONTROL3D_H
