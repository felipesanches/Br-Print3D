#include "vtkWidget2.h"

vtkWidget2::vtkWidget2()
{

}

void vtkWidget2::renderSTL(QString pathStl)
{

    vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName(pathStl.toStdString().c_str());
    reader->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(reader->GetOutputPort());

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    //vtkRenderWindowInteractor *r = this->GetRenderWindow()->GetInteractor();
    vtkRenderWindow* renderWindow = this->GetRenderWindow()->GetInteractor()->GetRenderWindow();
    //renderWindow->SetInteractor(r);

    renderWindow->AddRenderer(renderer);

    renderer->AddActor(actor);
    renderer->SetBackground(0, .5, 1); // Background color blue

    renderer->ResetCamera();
    renderWindow->Render();
}
