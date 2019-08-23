#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QtCharts>
#include <QtCharts/QAbstractAxis>
#include "serialcommunicator.h"


class MainWindow : public QWidget
{
    Q_OBJECT

public:

    MainWindow();

    bool formed(std::string const & s)
   {
       QString k;

       if (s.find_first_of(".\r@a") != std::string::npos) return false;
       else return true;
   }

private slots:

    void LED_ONOFF_CLICKED();
    void FLICKER_LED_CLICKED();
    void READ_CLICKED();

private:


    QFormLayout * top_box_layout;
    QPushButton LED_ON;
    QPushButton FLICKER_LED;
    QPushButton READ_BUTTON;
    QTextBrowser res;
    bool LED1_IS_ON = false;



    // DATA CHARTING
    QChartView *chartView;
    QtCharts::QChart *chart;
    QtCharts::QSplineSeries* series;
    QtCharts::QAreaSeries* evaluation_points;

    // SERIAL INTERACTION

    SerialCommunicator * s_com;


};



#endif // MAINWINDOW_H
