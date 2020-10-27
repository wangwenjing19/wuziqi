#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setFixedSize(800,550);
    w.setWindowTitle("团队项目：五子棋");
    return a.exec();
}
