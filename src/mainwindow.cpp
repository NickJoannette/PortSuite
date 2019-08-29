#include "mainwindow.h"
#include <QPushButton>
#include <QColor>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{



    // MENU
    MainWindowMenuBar* main_menu_bar = new MainWindowMenuBar(this);
    setMenuBar(main_menu_bar);

    // SERIAL COMM
    s_com = new SerialCommunicator(series);
    pcbw = new PortControlButtonWidget(s_com,this);

    // STYLE AND MAIN LAYOUT

    QWidget *topWidget = new QWidget;
    topWidget->setStyleSheet("background-color:black;");
    top_box_layout = new QHBoxLayout(topWidget);
    top_box_layout ->setSpacing(5);
    topWidget->setLayout(top_box_layout);
    topWidget->setMaximumHeight(450);
    setCentralWidget(topWidget);



    // COMMS Customization

    comms_panel_layout = new QHBoxLayout();
    comms_log.setFixedSize(150,90);
    comms_log.setStyleSheet("padding:5px; font-size: 12px; color: white; background-color: black; border:1px solid  rgb(44,205,112);");
    QString status = s_com->qsp->isOpen() ? "OPEN\n" : "CLOSED\n";
    comms_log.setText("Port:\n"
                      "Status: " + status +
                      "Bytes received: " + QString::number(total_bytes_read) +
                      "\nMean value: "  + QString::number(average_data_value) +"\n");

    // CHART VIEW

     series = new QtCharts::QSplineSeries();
     QFont font;
     font.setPixelSize(24);
     QColor darkgreen;
     darkgreen.setRgb(44,205,112);
     QPen pen(darkgreen);
     pen.setWidth(2);

    // Instantiating the Chart, Hiding the Legend, Adding the Series

    QtCharts::QChart *chart;
    chart = new QtCharts::QChart();
    chart->legend()->hide();
    chart->addSeries(series);

    // Setting the Chart Title

    chart->setTitle("E44 Hall Sensor");

    // Customizing the Chart

    chart->setBackgroundBrush(QBrush(Qt::white));
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0,200);
    chart->axes(Qt::Vertical).first()->setRange(0, 400);
    chart->axes(Qt::Horizontal).first()->setTitleText("Bytes Received");
    chart->axes(Qt::Vertical).first()->setTitleText("Relative Voltage Signal");
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QSize chartviewsize;
    chartviewsize.setHeight(325);
    chartviewsize.setWidth(550);
    chartView->setMinimumSize(chartviewsize);

    // POST-THEME CUSTOMIZATIONS
    chartView->chart()->setTheme(QChart::ChartThemeDark);
    chartView->setStyleSheet("background-color: black;");
    series->setPen(pen);
    chart->setTitleBrush(QBrush(Qt::white));
    chart->setTitleFont(font);
    chart->setDropShadowEnabled();
    chart->setBackgroundRoundness(0);


    // ADDING WIDGETS AND LAYOUTS TO MAIN LAYOUT

  //  addDockWidget(Qt::RightDockWidgetArea, pcbw);


   // pcbw->setFloating(true);
    QPoint mw = pos();
    int x = mw.x();
    int y =mw.y();
    pcbw->move(x-100,y-pcbw->height()+height()/2);
    top_box_layout->addWidget(chartView);
    top_box_layout->addWidget(&comms_log);

    // CONNECTING SIGNALS AND SLOTS

    connect(s_com,SIGNAL(send_chart_data(unsigned int, unsigned int)),this,SLOT(receive_chart_data(unsigned int, unsigned int)));
    connect(pcbw, SIGNAL(CLOSE_CLICKED()),this, SLOT(write_Closed()));
    connect(pcbw, SIGNAL(CLEAR_CLICKED()),this, SLOT(write_Cleared()));
    connect(pcbw, SIGNAL(RESET_CLICKED()),this, SLOT(write_Reset()));

}


void MainWindow::receive_chart_data(unsigned int br, unsigned int d)
{
   // qDebug() << "Received: " << br << ", " << d << "\n";
    total_bytes_read+=1;
    series->append(br, d);
    data_value_sum+=d;
    average_data_value = data_value_sum/total_bytes_read;
    comms_log.setText("Port: COM4\n"
                "Status: OPEN\n"
    "Bytes received: " + QString::number(total_bytes_read) +
    "\nMean value: "  + QString::number(average_data_value) +"\n");
}


void MainWindow::write_Opened()
{
    if (s_com->qsp->isOpen()) comms_log.setText("Port: COM4\n"
                                                "Status: OPEN\n"
                                                "Bytes received: " + QString::number(total_bytes_read) +
                                                "\nMean value: "  + QString::number(average_data_value) +"\n");

}

void MainWindow::write_Closed()
{
    comms_log.setText("Port: COM4\n"
                      "Status: CLOSED\n"
                      "Bytes received: " + QString::number(total_bytes_read) +
                      "\nMean value: "  + QString::number(average_data_value) +"\n");
}

void MainWindow::write_Cleared()
{
    series->clear();
    QString status = s_com->qsp->isOpen() ? "OPEN\n" : "CLOSED\n";
    comms_log.setText("Port: COM4\n"
                      "Status: " + status +
                      "Bytes received: " + QString::number(total_bytes_read) +
                      "\nMean value: "  + QString::number(average_data_value) +"\n");
}

void MainWindow::write_Reset()
{
    // chartView->chart()->setTheme(QChart::ChartThemeDark);
     total_bytes_read = 0;
     data_value_sum = 0;
     average_data_value = 0;
     QString status = s_com->qsp->isOpen() ? "OPEN\n" : "CLOSED\n";
     comms_log.setText("Port: COM4\n"
                       "Status: " + status +
                       "Bytes received: " + QString::number(total_bytes_read) +
                       "\nMean value: "  + QString::number(average_data_value) +"\n");
}

void MainWindow::moveEvent(QMoveEvent* event)
{
    pcbw->raise();
    pcbw->move(event->pos().x()-100,event->pos().y()-pcbw->height()+height()/2);

}

 void MainWindow::closeEvent(QCloseEvent* event)
 {

     pcbw->close();
 }
