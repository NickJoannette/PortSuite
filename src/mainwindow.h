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
    void receive_chart_data(unsigned int, unsigned int);

private:

    QVBoxLayout * com_button_layout;
    QVBoxLayout * top_box_layout;
    QGridLayout * comms_panel_layout;
    QPushButton LED_ON;
    QPushButton FLICKER_LED;
    QPushButton READ_BUTTON;
    QTextBrowser res;
    bool LED1_IS_ON = false;

    // UI SECTION LABELS
    // coms
    QLabel com_control_section_label;

    // charts
    QLabel charts_control_section_label;



    // DATA CHARTING
    QChartView *chartView;
    QtCharts::QChart *chart;
    QtCharts::QSplineSeries* series;
    QtCharts::QAreaSeries* evaluation_points;

    // SERIAL INTERACTION

    // Serial communicator
    SerialCommunicator * s_com;

    // Serial comms log text view
    QTextBrowser comms_log;

};



#endif // MAINWINDOW_H
