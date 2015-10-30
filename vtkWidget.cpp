#include <vtkWidget.h>


vtkWidget::vtkWidget(QVTKWidget *parent) :
    QVTKWidget(parent),
    ui(new Ui::vtkWidget)
{
    ui->setupUi(this);

}

vtkWidget::~vtkWidget()
{
    delete ui;
}
void vtkWidget::renderSTL(QString pathStl)
{
  vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
  reader->SetFileName(pathStl.toStdString().c_str());
  reader->Update();
 
  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(reader->GetOutputPort());
 
  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
 
  vtkSmartPointer<vtkRenderer> renderer =  vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  renderer->AddActor(actor);
  renderer->SetBackground(.3, .6, .3); // Background color green
 
  renderWindow->Render();
  renderWindowInteractor->Start();
   ui->getRenderWindow();

}
/*void vtkWidget::getRenderWindow(vtkSmartPointer<vtkRenderWindow> w)
{
  vtkRenderWindow* renderWindow = 
}*/