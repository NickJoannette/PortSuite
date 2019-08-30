#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);


    MainWindow w;
    w.setWindowTitle("Serial Control Beta");
    QSize max_window_size;

    max_window_size.setWidth(450);
    max_window_size.setHeight(350);
    w.setMaximumSize(max_window_size);
    w.show();

    return a.exec();
}
