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
    PortControlButtonWidget * pcbw = new PortControlButtonWidget(s_com);


    // STYLE AND MAIN LAYOUT

    QWidget *topWidget = new QWidget;
    topWidget->setStyleSheet("background-color:#474747;");


    top_box_layout = new QHBoxLayout(topWidget);
    top_box_layout ->setSpacing(5);
    topWidget->setLayout(top_box_layout);
    setCentralWidget(topWidget);



    // COMMS Customization

    QWidget *commsPanelWidget = new QWidget;
    comms_panel_layout = new QHBoxLayout(commsPanelWidget);

    // Setting comms log and other static memory member widgets' properties

    comms_log.setStyleSheet("padding:5px; font-size: 12px; color: white; background-color: black; border:1px solid  rgb(44,205,112);");
    QString status = s_com->qsp->isOpen() ? "OPEN\n" : "CLOSED\n";
    comms_log.setText("Port Status: " + status +
                      "Bytes received: " + QString::number(total_bytes_read) +
                      "\nMean value: "  + QString::number(average_data_value) +"\n");

    comms_log.setFixedSize(250,125);
    comms_panel_layout->setSpacing(0);
    transmission_label.setText("Transmission |");
    reception_label.setText("Reception |");



    // CHART VIEW

     QFont font;
     font.setPixelSize(24);

     // Instantiating and customizing the series plot; Setting the pen for drawing it

     series = new QtCharts::QSplineSeries();
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
    chartviewsize.setHeight(250);
    chartviewsize.setWidth(350);
    chartView->setMaximumSize(chartviewsize);

    // POST-THEME CUSTOMIZATIONS
    chartView->chart()->setTheme(QChart::ChartThemeDark);
     chartView->setStyleSheet("background-color: black;");
    series->setPen(pen);
    chart->setTitleBrush(QBrush(Qt::white));
    chart->setTitleFont(font);
    chart->setDropShadowEnabled();
    chart->setBackgroundRoundness(0);


    // ADDING WIDGETS AND LAYOUTS TO MAIN LAYOUT

    top_box_layout->addWidget(chartView);
    top_box_layout->addWidget(&comms_log);
    comms_panel_layout->addStretch(300);
    //comms_panel_layout->addWidget(comControlWidget);
   // comms_panel_layout->addWidget(&comms_log);
    //comms_panel_layout->setSizeConstraint(QLayout::SetMinimumSize);
    comms_panel_layout->addStretch(300);
  //  top_box_layout->addWidget(commsPanelWidget);

    connect(s_com,SIGNAL(send_chart_data(unsigned int, unsigned int)),this,SLOT(receive_chart_data(unsigned int, unsigned int)));
    connect(pcbw, SIGNAL(CLOSE_CLICKED()),this, SLOT(write_Closed()));
    connect(pcbw, SIGNAL(CLEAR_CLICKED()),this, SLOT(write_Cleared()));
    connect(pcbw, SIGNAL(RESET_CLICKED()),this, SLOT(write_Reset()));
}


void MainWindow::receive_chart_data(unsigned int br, unsigned int d)
{
    qDebug() << "Received: " << br << ", " << d << "\n";
    total_bytes_read+=1;
    series->append(br, d);
    data_value_sum+=d;
    average_data_value = data_value_sum/total_bytes_read;
    comms_log.setText("Port Status: OPEN\n"
    "Bytes received: " + QString::number(total_bytes_read) +
    "\nMean value: "  + QString::number(average_data_value) +"\n");
}


void MainWindow::write_Opened()
{
    if (s_com->qsp->isOpen()) comms_log.setText("Port Status: OPEN\n"
                                                "Bytes received: " + QString::number(total_bytes_read) +
                                                "\nMean value: "  + QString::number(average_data_value) +"\n");

}

void MainWindow::write_Closed()
{
    comms_log.setText("Port Status: CLOSED\n"
                      "Bytes received: " + QString::number(total_bytes_read) +
                      "\nMean value: "  + QString::number(average_data_value) +"\n");
}

void MainWindow::write_Cleared()
{
    series->clear();
    QString status = s_com->qsp->isOpen() ? "OPEN\n" : "CLOSED\n";
    comms_log.setText( "Port Status: " + status +
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
     comms_log.setText( "Port Status: " + status +
                       "Bytes received: " + QString::number(total_bytes_read) +
                       "\nMean value: "  + QString::number(average_data_value) +"\n");
}
