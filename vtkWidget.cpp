/*
 * This class has a deprecated library!
 * QVTKWidget is disused, so this class will not be used for long.
 * Only I'm working with her because I'm learning VTK and many Qt + VTK tutorials still use this library,
 * with time I will be carrying to the new class.
 * Thank you for your understanding.
 * Lays Rodrigues November 7,2015
 * */

#include "vtkWidget.h"

vtkWidget::vtkWidget()
{

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

      vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
      vtkRenderWindow *renderWindow = this->GetRenderWindow();
      renderWindow->AddRenderer(renderer);
      vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
      renderWindowInteractor->SetRenderWindow(renderWindow);

      renderer->AddActor(actor);
      renderer->SetBackground(0, .5, 1); // Background color blue

      renderWindow->Render();
      renderWindowInteractor->Start();


}
