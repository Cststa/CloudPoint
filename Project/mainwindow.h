#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDesktopWidget>
#include "subwidget.h"
#include "pcl_function.h"
#pragma execution_character_set("utf-8")
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    friend class subwidget;
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void CreateCloudFromTxt(const std::string& file_path, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);

private:
    Ui::MainWindow *ui;
    subwidget subw;


};
#endif // MAINWINDOW_H
