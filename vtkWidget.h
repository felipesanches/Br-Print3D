#include <QVTKWidget2.h>
#include <vtkPolyData.h>
#include <vtkSTLReader.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

namespace Ui {
class vtkWidget;
}

class vtkWidget : public QVTKWidget2
{
  Q_OBJECT
  
public:
  explicit vtkWidget(QVTKWidget2 *parent = 0);
  ~vtkWidget();
private:
  Ui::vtkWidget *ui;
  void renderSTL(QString pathStl);
  
};
  
  