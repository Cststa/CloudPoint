#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDesktopWidget *pDesk = QApplication::desktop();

    MainWindow w;
    //窗体显示
    w.show();
    //窗体居中
    w.move((pDesk->width() - w.width()) / 2, (pDesk->height() - w.height()) / 2);
 
    return a.exec();
}
