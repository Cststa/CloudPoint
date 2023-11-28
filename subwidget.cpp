#include "subwidget.h"
#include "ui_subwidget.h"


subwidget::subwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::subwidget)
{
    ui->setupUi(this);
    //�Ӵ����游���ڶ��ر�
    this->setAttribute(Qt::WA_QuitOnClose, false);
    
    //���ô��ڱ���
    setWindowTitle("��ά���ƿ��ӻ�ƽ̨");
    //connect(ui->pushButton, SIGNAL(triggered), this, SLOT(on_pushButton_clicked()));

    //��ȡ��ǰ��Ļ�ֱ���
    QDesktopWidget w;
    QDesktopWidget* pDeskdop = QApplication::desktop();
    int deskWidth = w.width() * 0.75;
    int deskHeight = w.height() * 0.69;
    int posX = (pDeskdop->width() - deskWidth) / 2;
    int posY = (pDeskdop->height() - deskHeight) / 1.41;

    //���ô��ڴ�С
    //this->resize(deskWidth, deskHeight);
    setGeometry(posX, posY, deskWidth, deskHeight);

    //��ʼ��VTK�ؼ�
    //initVTK();


}


subwidget::~subwidget()
{
    delete ui;
}

//������Ƹ���
unsigned long long CaculatePointNumber(pcl::PointCloud<pcl::PointXYZRGB> cloud)
{
    int count = 0;
    for (int i = 0; i < cloud.size(); ++i) {
        ++count;
    }
    return count;
}
//������ͼ������ͼ��ʾ
void subwidget::PointOriginalAndThreeViewDisplay()
{
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkUnsignedCharArray> colors = vtkSmartPointer<vtkUnsignedCharArray>::New();

    colors->SetNumberOfComponents(3); // Set the number of components to 3 (RGB)
    colors->SetName("Colors");

    for (size_t i = 0; i < cloud.size(); ++i) {
        pcl::PointXYZRGB p = cloud.at(i);
        points->InsertNextPoint(p.x, p.y, p.z);

        unsigned char color[3] = { p.r, p.g, p.b };
        colors->InsertNextTypedTuple(color);
    }

    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
    polydata->SetPoints(points);
    polydata->GetPointData()->SetScalars(colors);
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkPolyDataMapper> mapper1 = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkPolyDataMapper> mapper2 = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkPolyDataMapper> mapper3 = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter = vtkSmartPointer<vtkVertexGlyphFilter>::New();

    vertexFilter->SetInputData(polydata);
    vertexFilter->Update();

    mapper->SetInputConnection(vertexFilter->GetOutputPort());
    mapper1->SetInputConnection(vertexFilter->GetOutputPort());
    //mapper1->ScalarVisibilityOff();
    mapper2->SetInputConnection(vertexFilter->GetOutputPort());
    mapper3->SetInputConnection(vertexFilter->GetOutputPort());

    // ����VTK��actor
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // ����VTK��actor
    vtkSmartPointer<vtkActor> actor1 = vtkSmartPointer<vtkActor>::New();
    actor1->SetMapper(mapper1);

    // ����VTK��actor
    vtkSmartPointer<vtkActor> actor2 = vtkSmartPointer<vtkActor>::New();
    actor2->SetMapper(mapper2);

    // ����VTK��actor
    vtkSmartPointer<vtkActor> actor3 = vtkSmartPointer<vtkActor>::New();
    actor3->SetMapper(mapper3);

    // ��actor��ӵ�renderer��
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->RemoveAllViewProps();
    renderer->AddActor(actor);

    // ��actor��ӵ�renderer��
    vtkSmartPointer<vtkRenderer> renderer1 = vtkSmartPointer<vtkRenderer>::New();
    renderer1->RemoveAllViewProps();
    renderer1->AddActor(actor1);

    // ��actor��ӵ�renderer��
    vtkSmartPointer<vtkRenderer> renderer2 = vtkSmartPointer<vtkRenderer>::New();
    renderer2->RemoveAllViewProps();
    renderer2->AddActor(actor2);

    // ��actor��ӵ�renderer��
    vtkSmartPointer<vtkRenderer> renderer3 = vtkSmartPointer<vtkRenderer>::New();
    renderer3->RemoveAllViewProps();
    renderer3->AddActor(actor3);


    //���ñ�����ɫ
    renderer->SetBackground(0.83, 0.83, 0.83);
    renderer1->SetBackground(0.83, 0.83, 0.75);
    renderer2->SetBackground(0.75, 0.85, 1);
    renderer3->SetBackground(1, 0.8, 0.6);

    // ��renderer��ӵ�vtkRenderWindow��
    auto renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    auto renderWindow1 = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    auto renderWindow2 = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    auto renderWindow3 = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();


    //�������λ��
    renderer->GetActiveCamera()->SetPosition(0, 0, 1);
    renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
    renderer->GetActiveCamera()->SetViewUp(0, 1, 0);

    renderer1->GetActiveCamera()->SetPosition(0, 0, 1);
    renderer1->GetActiveCamera()->SetFocalPoint(0, 0, 0);
    renderer1->GetActiveCamera()->SetViewUp(0, 1, 0);

    renderer2->GetActiveCamera()->SetPosition(-1, 0, 0);
    renderer2->GetActiveCamera()->SetFocalPoint(0, 0, 0);
    renderer2->GetActiveCamera()->SetViewUp(0, 1, 0);

    renderer3->GetActiveCamera()->SetPosition(0, 1, 0);
    renderer3->GetActiveCamera()->SetFocalPoint(0, 1, 0);
    renderer3->GetActiveCamera()->SetViewUp(0, 0, -1);
    

    //��ӵ���Ⱦ����
    renderWindow->AddRenderer(renderer);
    renderWindow1->AddRenderer(renderer1);
    renderWindow2->AddRenderer(renderer2);
    renderWindow3->AddRenderer(renderer3);

    //�������
    renderer->ResetCamera();
    renderer1->ResetCamera();
    renderer2->ResetCamera();
    renderer3->ResetCamera();

    
    ui->qvtkWidget->SetRenderWindow(renderWindow);
    ui->frontqvtk->SetRenderWindow(renderWindow1);
    ui->leftqvtk->SetRenderWindow(renderWindow2);
    ui->topqvtk->SetRenderWindow(renderWindow3);

    //�ص����� ʵ�����Эͬ��ת
    vtkSmartPointer<vtkCameraCallback> cameraCallback = vtkSmartPointer<vtkCameraCallback>::New();
    cameraCallback->renderer = renderer;
    cameraCallback->renderer1 = renderer1;
    cameraCallback->renderer2 = renderer2;
    cameraCallback->renderer3 = renderer3;

    ui->qvtkWidget->GetRenderWindow()->GetInteractor()->AddObserver(vtkCommand::TimerEvent, cameraCallback);
    ui->qvtkWidget->GetRenderWindow()->GetInteractor()->CreateRepeatingTimer(10);
    ui->frontqvtk->GetRenderWindow()->GetInteractor()->AddObserver(vtkCommand::TimerEvent, cameraCallback);
    ui->frontqvtk->GetRenderWindow()->GetInteractor()->CreateRepeatingTimer(10);
    ui->leftqvtk->GetRenderWindow()->GetInteractor()->AddObserver(vtkCommand::TimerEvent, cameraCallback);
    ui->leftqvtk->GetRenderWindow()->GetInteractor()->CreateRepeatingTimer(10);
    ui->topqvtk->GetRenderWindow()->GetInteractor()->AddObserver(vtkCommand::TimerEvent, cameraCallback);
    ui->topqvtk->GetRenderWindow()->GetInteractor()->CreateRepeatingTimer(10);



}


void CreateCloudFromTxt(const std::string& file_path, pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud)
{
    std::ifstream file(file_path.c_str());
    std::string line;
    pcl::PointXYZRGB point;
    //float nx, ny, nz;
    while (getline(file, line)) {
        std::stringstream ss(line);
        ss >> point.x;
        ss >> point.y;
        ss >> point.z;
        //ss >> nx;
        //ss >> ny;
        //ss >> nz;
        cloud->push_back(point);
    }
    file.close();
}

//��ȡ�ļ�����ʾ 
void subwidget::openFilePCL(QString fileName)
{
    if (fileName.endsWith("ply"))
    {
        qDebug() << fileName;
        if (pcl::io::loadPLYFile<pcl::PointXYZRGB>(fileName.toStdString(), cloud) == -1) //* load the file
        {
            qDebug() << "Couldn't read file  \n";
            return;
        }
    }
    else if (fileName.endsWith("pcd"))
    {
        qDebug() << fileName;
        if (pcl::io::loadPCDFile<pcl::PointXYZRGB>(fileName.toStdString(), cloud) == -1) //* load the file
        {
            qDebug() << "Couldn't read pcd file  \n";
            return;
        }
    }
    else if (fileName.endsWith("txt"))
    {
        qDebug() << fileName;
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloudTemp(new pcl::PointCloud<pcl::PointXYZRGB>);
        CreateCloudFromTxt(fileName.toStdString(), cloudTemp);
        cloud = *cloudTemp;
    }
    else {
        QMessageBox::warning(this, "Warning", "���ƶ�ȡ��ʽ����");
    }


    //viewer->removeAllPointClouds();
    //viewer->removeAllShapes();
    PointOriginalAndThreeViewDisplay();

    //vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    //vtkSmartPointer<vtkUnsignedCharArray> colors = vtkSmartPointer<vtkUnsignedCharArray>::New();

    //colors->SetNumberOfComponents(3); // Set the number of components to 3 (RGB)
    //colors->SetName("Colors");

    //for (size_t i = 0; i < cloud.size(); ++i) {
    //    pcl::PointXYZRGB p = cloud.at(i);
    //    points->InsertNextPoint(p.x, p.y, p.z);

    //    unsigned char color[3] = { p.r, p.g, p.b };
    //    colors->InsertNextTypedTuple(color);
    //}

    //vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
    //polydata->SetPoints(points);
    //polydata->GetPointData()->SetScalars(colors);
    //vtkSmartPointer<vtkPolyDataMapper> mapper1 = vtkSmartPointer<vtkPolyDataMapper>::New();
    //vtkSmartPointer<vtkPolyDataMapper> mapper2 = vtkSmartPointer<vtkPolyDataMapper>::New();
    //vtkSmartPointer<vtkPolyDataMapper> mapper3 = vtkSmartPointer<vtkPolyDataMapper>::New();
    //vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter = vtkSmartPointer<vtkVertexGlyphFilter>::New();

    //vertexFilter->SetInputData(polydata);

    //vertexFilter->Update();

    //mapper1->SetInputConnection(vertexFilter->GetOutputPort());
    ////mapper1->ScalarVisibilityOff();
    //mapper2->SetInputConnection(vertexFilter->GetOutputPort());
    //mapper3->SetInputConnection(vertexFilter->GetOutputPort());

    //// ����VTK��actor
    //vtkSmartPointer<vtkActor> actor1 = vtkSmartPointer<vtkActor>::New();
    //actor1->SetMapper(mapper1);

    //// ����VTK��actor
    //vtkSmartPointer<vtkActor> actor2 = vtkSmartPointer<vtkActor>::New();
    //actor2->SetMapper(mapper2);

    //// ����VTK��actor
    //vtkSmartPointer<vtkActor> actor3 = vtkSmartPointer<vtkActor>::New();
    //actor3->SetMapper(mapper3);

    //// ��actor��ӵ�renderer��
    //vtkSmartPointer<vtkRenderer> renderer1 = vtkSmartPointer<vtkRenderer>::New();
    ////renderer1->SetViewport(0, 0, 0.33, 1);
    //renderer1->AddActor(actor1);

    //// ��actor��ӵ�renderer��
    //vtkSmartPointer<vtkRenderer> renderer2 = vtkSmartPointer<vtkRenderer>::New();
    ////renderer2->SetViewport(0, 0, 0.33, 1);
    //renderer2->AddActor(actor2);

    //// ��actor��ӵ�renderer��
    //vtkSmartPointer<vtkRenderer> renderer3 = vtkSmartPointer<vtkRenderer>::New();
    ////renderer3->SetViewport(0, 0, 0.33, 1);
    //renderer3->AddActor(actor3);

    ////���ñ�����ɫ
    //renderer1->SetBackground(0.83, 0.83, 0.75);
    //renderer2->SetBackground(0.75, 0.85, 1);
    //renderer3->SetBackground(1, 0.8, 0.6);

    //// ��renderer��ӵ�vtkRenderWindow��
    //auto renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    //auto renderWindow2 = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    //auto renderWindow3 = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();

    //renderWindow->AddRenderer(renderer1);
    //renderWindow2->AddRenderer(renderer2);
    //renderWindow3->AddRenderer(renderer3);

    //renderer1->GetActiveCamera()->SetPosition(0, 0, 1);
    //renderer1->GetActiveCamera()->SetFocalPoint(0, 0, 0);
    //renderer1->GetActiveCamera()->SetViewUp(0, 1, 0);

    //renderer2->GetActiveCamera()->SetPosition(-1, 0, 0);
    //renderer2->GetActiveCamera()->SetFocalPoint(0, 0, 0);
    //renderer2->GetActiveCamera()->SetViewUp(0, 1, 0);

    //renderer3->GetActiveCamera()->SetPosition(0, 1, 0);
    //renderer3->GetActiveCamera()->SetFocalPoint(0, 0, 0);
    //renderer3->GetActiveCamera()->SetViewUp(0, 0, -1);

    //renderer1->ResetCamera();
    //renderer2->ResetCamera();
    //renderer3->ResetCamera();

    ////ui->qvtkWidget->SetRenderWindow(renderWindow);
    //ui->frontqvtk->SetRenderWindow(renderWindow);
    //ui->leftqvtk->SetRenderWindow(renderWindow2);
    //ui->topqvtk->SetRenderWindow(renderWindow3);

    ////ui->qvtkWidget->SetRenderWindow(renderWindow);
    //ui->frontqvtk->SetRenderWindow(renderWindow);
    //ui->leftqvtk->SetRenderWindow(renderWindow2);
    //ui->topqvtk->SetRenderWindow(renderWindow3);

    //boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer2 = viewer;
    //boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer3 = viewer;
    //boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer4 = viewer;

    //auto renderer2 = vtkSmartPointer<vtkRenderer>::New();
    //auto renderWindow2 = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();

    //auto renderer3 = vtkSmartPointer<vtkRenderer>::New();
    //auto renderWindow3 = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();

    //auto renderer4 = vtkSmartPointer<vtkRenderer>::New();
    //auto renderWindow4 = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();


    //renderWindow2->AddRenderer(renderer2);
    //renderWindow3->AddRenderer(renderer3);
    //renderWindow4->AddRenderer(renderer4);

    //viewer2.reset(new pcl::visualization::PCLVisualizer(renderer2, renderWindow2, "viewer2", false));
    //viewer3.reset(new pcl::visualization::PCLVisualizer(renderer3, renderWindow3, "viewer3", false));
    //viewer4.reset(new pcl::visualization::PCLVisualizer(renderer4, renderWindow4, "viewer4", false));

    ////��
    //ui->frontqvtk->setRenderWindow(viewer2->getRenderWindow());
    //viewer2->setupInteractor(ui->frontqvtk->interactor(), ui->frontqvtk->renderWindow());
    ////��
    //ui->leftqvtk->setRenderWindow(viewer3->getRenderWindow());
    //viewer3->setupInteractor(ui->leftqvtk->interactor(), ui->leftqvtk->renderWindow());
    ////��
    //ui->topqvtk->setRenderWindow(viewer4->getRenderWindow());
    //viewer4->setupInteractor(ui->topqvtk->interactor(), ui->topqvtk->renderWindow());

    //viewer2->setBackgroundColor(0.1, 0.2, 0.2);
    //viewer3->setBackgroundColor(0.1, 0.4, 0.2);
    //viewer4->setBackgroundColor(0.3, 0.5, 0.2);
    //

    //viewer->removeAllPointClouds();
    ////viewer->removeAllShapes();
    //viewer->addPointCloud(cloud.makeShared(), "sample cloud");
    //viewer2->addPointCloud(cloud.makeShared(), "sample cloud2");
    //viewer3->addPointCloud(cloud.makeShared(), "sample cloud3");
    //viewer4->addPointCloud(cloud.makeShared(), "sample cloud4");

    //pcl::visualization::Camera camera;



    //viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");
    //viewer->addCoordinateSystem(0.5);

    //viewer->resetCamera();



    //ui->qvtkWidget->update();
    //ui->frontqvtk->update();






    //�ļ�·����ʾ
    QFileInfo fileInfo(fileName);
    QString str1 = "Location��" + fileInfo.canonicalFilePath();
    ui->label->setText(str1);

    //����������ʾ
    QString str2 = "Point Cloud Number��" + QString::number(CaculatePointNumber(cloud));
    ui->label_2->setText(str2);


}

//int subwidget::on_pushButton_clicked()
//{
//
//
//    QMessageBox::warning(this, "Warning", "����");
//    // �������ӻ�����
//    pcl::visualization::PCLVisualizer viewer_1("viewer_1");
//    pcl::visualization::PCLVisualizer viewer_2("viewer_2");
//    pcl::visualization::PCLVisualizer viewer_3("viewer_3");
//
//    // ���2d���ֱ�ǩ
//    viewer_1.addText("front view", 10, 10, 20, 1, 0, 0, "viewport_v1");
//    viewer_2.addText("side view", 10, 10, 20, 1, 0, 0, "viewport_v2");
//    viewer_3.addText("vertical view", 10, 10, 20, 1, 0, 0, "viewport_v3");
//
//    // ���3d���ֱ�ǩ
//    pcl::PointXYZ pos_3d_text = { 0.1,0.1,0.1 };
//    viewer_1.addText3D("3d_v1", pos_3d_text, 0.1, 0, 1, 0, "3d_text_v1");
//    viewer_2.addText3D("3d_v2", pos_3d_text, 0.1, 0, 1, 0, "3d_text_v2");
//    viewer_3.addText3D("3d_v3", pos_3d_text, 0.1, 0, 1, 0, "3d_text_v3");
//
//    // �������ϵ
//    viewer_1.addCoordinateSystem(0.5);    // ��λ��m
//    viewer_2.addCoordinateSystem(0.5);    // ��λ��m
//    viewer_3.addCoordinateSystem(0.5);    // ��λ��m
//
//    // ���ÿ��ӻ����ڱ���ɫ
//    viewer_1.setBackgroundColor(239 * 1.0 / 255, 234 * 1.0 / 255, 1);     // r,g,b  0~1֮��
//    viewer_2.setBackgroundColor(242 * 1.0 / 255, 1, 216 * 1.0 / 255);     // r,g,b  0~1֮��
//    viewer_3.setBackgroundColor(211 * 1.0 / 255, 1, 248 * 1.0 / 255);     // r,g,b  0~1֮��
//
//    // �������������
//    viewer_1.initCameraParameters();
//    viewer_2.initCameraParameters();
//    viewer_3.initCameraParameters();
//
//    // ��v1��������ӵ���
//    viewer_1.addPointCloud(cloud.makeShared(), "cloud_src_1");
//    viewer_2.addPointCloud(cloud.makeShared(), "cloud_src_2");
//    viewer_3.addPointCloud(cloud.makeShared(), "cloud_src_3");
//
//    pcl::visualization::Camera camera;
//    // �رմ������˳�
//    while (!viewer_1.wasStopped() && !viewer_2.wasStopped() && !viewer_3.wasStopped()) {
//        viewer_1.spinOnce(1);
//        viewer_2.spinOnce(1);
//        viewer_3.spinOnce(1);
//
//        viewer_1.getCameraParameters(camera);
//
//        viewer_2.setCameraPosition( // ����ͼ
//            -camera.pos[2], camera.pos[1], -camera.pos[0],
//            camera.focal[0], camera.focal[1], camera.focal[2],  //  ���㱣�ֲ���
//            camera.view[0], camera.view[1], camera.view[2]); //  ������߱������������������ֱ
//
//        viewer_3.setCameraPosition(
//            camera.pos[0], -camera.pos[2], -camera.pos[1],
//            camera.focal[0], camera.focal[1], camera.focal[2], //  ����λ�ñ��ֲ���
//            -camera.pos[0], -camera.pos[1], -camera.pos[2]);
//
//    }
//
//    return 0;
//}
