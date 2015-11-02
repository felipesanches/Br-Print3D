#include "vtkWidget.h"

vtkWidget::vtkWidget()
{

}
void vtkWidget::renderSTL(QString pathStl)
{
vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
reader->SetFileName(pathStl.toStdString().c_str());
reader->Update();

vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
mapper->SetInputConnection(reader->GetOutputPort());

vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
actor->SetMapper(mapper);

vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
vtkRenderWindowInteractor *r = this->GetRenderWindow()->GetInteractor();
vtkRenderWindow* renderWindow = vtkRenderWindow::New();
r->SetRenderWindow(renderWindow);
renderWindow->AddRenderer(renderer);

renderer->AddActor(actor);
renderer->SetBackground(.0, .5, 1); // Background color green

renderer->ResetCamera();
renderWindow->Render();

}
/*
 * vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
reader->SetFileName(pathStl.toStdString().c_str());
reader->Update();

vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
mapper->SetInputConnection(reader->GetOutputPort());

vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
actor->SetMapper(mapper);

vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
vtkRenderWindowInteractor *r = this->GetRenderWindow()->GetInteractor();
vtkRenderWindow* renderWindow = vtkRenderWindow::New();
r->SetRenderWindow(renderWindow);
renderWindow->AddRenderer(renderer);

renderer->AddActor(actor);
renderer->SetBackground(.0, .5, 1); // Background color green

renderer->ResetCamera();
renderWindow->Render();
*/
