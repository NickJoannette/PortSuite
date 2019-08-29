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
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include "exportdialog.h"
#include "mainwindowmenubar.h"
#include "portcontrolbuttonwidget.h"

class MainWindow : public QMainWindow
{
    friend class PortControlButtonWidget;
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);

    bool formed(std::string const & s)
   {
       QString k;

       if (s.find_first_of(".\r@a") != std::string::npos) return false;
       else return true;
   }

private slots:

    void write_Opened();
    void write_Closed();
    void write_Cleared();
    void write_Reset();

    void receive_chart_data(unsigned int, unsigned int);



private:


    QHBoxLayout * top_box_layout;
    QHBoxLayout* comms_panel_layout;

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

    // Layout Partition Labels

    QLabel transmission_label;
    QLabel reception_label;


    // Buttons and variables

    unsigned int total_bytes_read = 0;

    // Serial communicator
    SerialCommunicator * s_com;

    // Serial comms log text view
    QLabel comms_log;

    // Serial Data Management
    unsigned int data_value_sum = 0;
    float average_data_value = 0;


};



#endif // MAINWINDOW_H
