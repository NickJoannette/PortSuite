#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);


    MainWindow w;
    w.setWindowTitle("Arduino to Qt Serial Interface");
     MainWindow x,y;
     x.show();
     y.show();
    w.show();

    return a.exec();
}
