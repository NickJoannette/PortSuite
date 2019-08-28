#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);


    MainWindow w;
    w.setWindowTitle("Arduino to Qt Serial Interface");
    w.resize(800,800);
    w.show();
    w.setGeometry(
                      QStyle::alignedRect(
                          Qt::LeftToRight,
                          Qt::AlignCenter,
                          w.size(),
                          qApp->desktop()->availableGeometry()
                      ));
    return a.exec();
}
