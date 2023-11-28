#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>
#include "pcl_function.h"
#pragma execution_character_set("utf-8")
//-----------------------------vtk---------------------------------
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <QVTKOpenGLWidget.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkGenericOpenGLRenderWindow.h> 
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkCamera.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSmartPointer.h> 
#include <QVTKInteractor.h>
#include <vtkRenderWindowInteractor3D.h>
#include <QVTKRenderWidget.h>
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>
#include <vtkUnsignedCharArray.h>
#include <QVTKRenderWindowAdapter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRendererCollection.h>
#include <vtkRenderWindowInteractor.h>
//-----------------------------vtk---------------------------------
#include <QDebug>
#include <QColorDialog>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QTime>
#include <QDir>
#include <QFile>
#include <QtMath>
#include <QDirIterator>
#include <string>

namespace Ui {
    class subwidget;
}

class subwidget : public QWidget
{
    friend class mainwindow;
    Q_OBJECT

public:
    explicit subwidget(QWidget *parent = nullptr);
    ~subwidget();
    void PointOriginalAndThreeViewDisplay();
    void openFilePCL(QString fileName);

    
private:
    Ui::subwidget *ui;
    pcl::PointCloud<pcl::PointXYZRGB> cloud;
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
    vtkSmartPointer<vtkCamera> camera;
private slots:
    //int on_pushButton_clicked();

};

#endif // SUBWIDGET_H
class vtkCameraCallback : public vtkCommand
{
public:
    static vtkCameraCallback* New()
    {
        return new vtkCameraCallback;
    }

    virtual void Execute(vtkObject* caller, unsigned long, void*)
    {
        vtkRenderWindowInteractor* interactor = static_cast<vtkRenderWindowInteractor*>(caller);

        // 获取四个相机
        vtkSmartPointer<vtkCamera> camera = renderer->GetActiveCamera();
        vtkSmartPointer<vtkCamera> camera1 = renderer1->GetActiveCamera();
        vtkSmartPointer<vtkCamera> camera2 = renderer2->GetActiveCamera();
        vtkSmartPointer<vtkCamera> camera3 = renderer3->GetActiveCamera();

        //camera1->SetPosition(position[0] * cos(angle) - position[1] * sin(angle), position[0] * sin(angle) + position[1] * cos(angle), position[2]);
        camera->SetViewUp(0, 1, 0);
        //camera2->SetPosition(camera1->GetPosition()[0], camera1->GetPosition()[1], camera1->GetPosition()[0]);
        //camera2->SetViewUp(0, 0, -1);
        //camera3->SetPosition(camera1->GetPosition()[1], camera1->GetPosition()[0], camera1->GetPosition()[0]);
        //camera3->SetViewUp(0, 1, 0);

        camera1->SetPosition(camera->GetPosition());
        camera1->SetViewUp(0, 1, 0);
        camera2->SetPosition(camera1->GetPosition()[2], camera1->GetPosition()[1], camera1->GetPosition()[0]);
        camera2->SetViewUp(0, 1, 0);
        camera3->SetPosition(camera1->GetPosition()[1], camera1->GetPosition()[2], camera1->GetPosition()[0]);
        camera3->SetViewUp(0, 1, 0);


        // 更新渲染
        renderer->GetRenderWindow()->Render();
        renderer1->GetRenderWindow()->Render();
        renderer2->GetRenderWindow()->Render();
        renderer3->GetRenderWindow()->Render();
    }

    vtkRenderer* renderer;
    vtkRenderer* renderer1;
    vtkRenderer* renderer2;
    vtkRenderer* renderer3;
};