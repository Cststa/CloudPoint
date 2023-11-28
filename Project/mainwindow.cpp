#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QFileDialog>

//按钮头文件

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*按屏幕比例设置窗体大小*/
    //获取当前屏幕分辨率
    QDesktopWidget w;
    int deskWidth = w.width();
    int deskHeight = w.height();

    //设置窗口大小
    this->resize(deskWidth * 0.75, deskHeight * 0.75);

    //设置窗口标题
    setWindowTitle("三维点云可视化平台");
}



MainWindow::~MainWindow()
{
    delete ui;
    
}

void MainWindow::CreateCloudFromTxt(const std::string& file_path, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
{
    std::ifstream file(file_path.c_str());
    std::string line;
    pcl::PointXYZ point;
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


//读取PCL文件
void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"打开文件","C:\\Users\\end\\Desktop","*.ply *.pcd *.obj *txt;;(*)All Files");
    
    if (!fileName.isEmpty()) {
        subw.show();
        subw.openFilePCL(fileName);
    }
    

}

