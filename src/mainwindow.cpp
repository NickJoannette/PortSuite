#include "mainwindow.h"
#include <QPushButton>
#include <QColor>
#include <iostream>
MainWindow::MainWindow()
{

    // SERIAL COMM
    s_com = new SerialCommunicator(series);

    // STYLE AND MAIN LAYOUT
    setStyleSheet("background-color: saddlebrown");
    QWidget *topWidget = new QWidget;
    QWidget *comControlWidget = new QWidget;
    top_box_layout = new QVBoxLayout(topWidget);
    top_box_layout ->setSpacing(5);
    setLayout(top_box_layout);

    // COM BUTTON LAYOUT
    QWidget *commsPanelWidget = new QWidget;
    comms_panel_layout = new QHBoxLayout(commsPanelWidget);

    // Setting comms log and other static memory member widgets' properties
    comms_log.setTextBackgroundColor(Qt::lightGray);
    comms_log.setStyleSheet("background-color: white; border: solid 1px black;float:left;");
    comms_log.setText("Bytes received: 24");
    comms_log.setFixedSize(100,50);
    comms_panel_layout->setSpacing(5);


    QSpacerItem height_spacer_100(100,100);
    com_button_layout = new QVBoxLayout(comControlWidget);
   // com_button_layout->addItem(&height_spacer_100);
    com_button_layout->setSpacing(0);
    com_button_layout->addWidget(&LED_ON);
    com_button_layout->addWidget(&FLICKER_LED);
    com_button_layout->addWidget(&READ_BUTTON);
    LED_ON.setFixedSize(70,30);FLICKER_LED.setFixedSize(70,30);READ_BUTTON.setFixedSize(70,30);

    // CHART VIEW

    QFont font;
     font.setPixelSize(24);

     // Setting and customizing the series plot
     series = new QtCharts::QSplineSeries();
     QPen pen(Qt::black);
     pen.setWidth(2);
     series->setPen(pen);

     // Setting the chart
    QtCharts::QChart *chart;
    chart = new QtCharts::QChart();
    chart->legend()->hide();
    chart->addSeries(series);

    // Setting the Title

    chart->setTitle("E44 Hall Sensor");

    // Customizing the Chart Background

    chart->setBackgroundBrush(QBrush(Qt::white));

    //
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0,200);
    chart->axes(Qt::Vertical).first()->setRange(0, 400);
    chart->axes(Qt::Horizontal).first()->setTitleText("Bytes Received");
    chart->axes(Qt::Vertical).first()->setTitleText("Relative Voltage Signal");
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QSize chartviewsize;
    chartView->setStyleSheet("background-color: cornsilk");
    chartviewsize.setHeight(350);
    chartviewsize.setWidth(600);
    chartView->setMinimumSize(chartviewsize);

    // POST-THEME CUSTOMIZATIONS
    chartView->chart()->setTheme(QChart::ChartThemeBrownSand);
    chart->setTitleBrush(QBrush(Qt::black));
    chart->setTitleFont(font);


    // LED SETTINGS
    LED_ON.setText("Open COM4");
    FLICKER_LED.setText("Close COM4");
    LED_ON.setStyleSheet("padding: 3px; background-color: darkgrey; color: black; border: 1px ridge black;");
    FLICKER_LED.setStyleSheet("padding: 3px; background-color: darkgrey; color: black; border: 1px ridge black;");
    READ_BUTTON.setText("Clear Data");
    READ_BUTTON.setStyleSheet("padding: 3px; background-color: darkgrey; color: black; border: 1px ridge black;");

    // ADDING WIDGETS AND LAYOUTS TO MAIN LAYOUT
    top_box_layout->addWidget(chartView);
    comControlWidget->setMaximumWidth(200);
    comms_panel_layout->addWidget(comControlWidget); comms_panel_layout->addWidget(&comms_log);
    top_box_layout->addWidget(commsPanelWidget);

    connect(&LED_ON,SIGNAL(clicked()),this,SLOT(LED_ONOFF_CLICKED()));
    connect(&FLICKER_LED,SIGNAL(clicked()),this,SLOT(FLICKER_LED_CLICKED()));
    connect(&READ_BUTTON,SIGNAL(clicked()),this,SLOT(READ_CLICKED()));
    connect(s_com,SIGNAL(send_chart_data(unsigned int, unsigned int)),this,SLOT(receive_chart_data(unsigned int, unsigned int)));
}


void MainWindow::receive_chart_data(unsigned int br, unsigned int d)
{
    qDebug() << "Received: " << br << ", " << d << "\n";

    series->append(br, d);
}
void MainWindow::LED_ONOFF_CLICKED()
{
    if (!s_com->qsp->isOpen())s_com->qsp->open(QIODevice::WriteOnly);

    if (s_com->qsp->isOpen() && s_com->qsp->isWritable())
                {
                    QByteArray * ba;
                    if (LED1_IS_ON == false)
                    {
                        ba = new QByteArray("A");
                        qDebug() << "Turned on." << endl;
                        LED1_IS_ON = true;
                    }
                    else
                    {
                        ba = new QByteArray("B");
                        LED1_IS_ON = false;
                    }

                    s_com->qsp->write(*ba);
                    s_com->qsp->flush();
                    s_com->qsp->close();
                }

}

void MainWindow::FLICKER_LED_CLICKED()
{
     if (!s_com->qsp->isOpen())s_com->qsp->open(QIODevice::WriteOnly);

     if (s_com->qsp->isOpen() && s_com->qsp->isWritable())
                {
                        for (int i = 0; i < 10; ++i)
                        {
                           if (!s_com->qsp->isOpen()) s_com->qsp->open(QIODevice::WriteOnly);
                           s_com->qsp->write(QByteArray("A"));
                           s_com->qsp->flush();

                           s_com->qsp->close();
                           QThread::msleep(25);
                           s_com->qsp->open(QIODevice::WriteOnly);
                          s_com-> qsp->write(QByteArray("B"));
                          s_com-> qsp->flush();

                           s_com->qsp->close();
                           QThread::msleep(25);

                        }

                }

}

void MainWindow::READ_CLICKED()
{
   s_com->bytes_read = 0;
   series->clear();
}
