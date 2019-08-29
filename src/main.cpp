#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);


    MainWindow w;
    w.setWindowTitle("Serial Control Beta");
     MainWindow x,y;
     x.show();
     y.show();
    w.show();

    return a.exec();
}
