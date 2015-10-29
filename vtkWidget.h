#include <QVTKWidget.h>

namespace Ui {
class QVTKWidget;
}

class vtkWidget : public QVTKWidget
{
  Q_OBJECT
  
public:
  explicit vtkWidget(QVTKWidget *parent = 0);
  ~vtkWidget();
private:
  Ui::vtkWidget *ui;
}
  
  