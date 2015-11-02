#ifndef VTKWIDGET2_H
#define VTKWIDGET2_H
#include <QVTKWidget2.h>
#include <vtkPolyData.h>
#include <vtkSTLReader.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkGenericOpenGLRenderWindow.h>

class vtkWidget : public QVTKWidget2
{
public:
    vtkWidget();
    void renderSTL(QString path);
};

#endif // VTKWIDGET2_H
