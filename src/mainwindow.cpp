#include "mainwindow.h"
#include <QPushButton>
#include <QColor>
#include <iostream>
MainWindow::MainWindow()
{

    // SERIAL COMM
    s_com = new SerialCommunicator(series);

    // STYLE AND MAIN LAYOUT
    setStyleSheet("background-color: darkblue");
    QWidget *topWidget = new QWidget;
    top_box_layout = new QFormLayout(topWidget);
    setLayout(top_box_layout);

    // COM BUTTON LAYOUT
    com_button_layout = new QHBoxLayout();
    com_button_layout->addWidget(&LED_ON);
    com_button_layout->addWidget(&FLICKER_LED);
    com_button_layout->addWidget(&READ_BUTTON);


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

    // Customizing the Title
    chart->setTitleBrush(QBrush(Qt::black));
    chart->setTitleFont(font);
    chart->setTitle("E44 Hall Sensor");

    // Customizing the Background

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
    chartView->setStyleSheet("background-color: 2a4d10");
    chartviewsize.setHeight(350);
    chartviewsize.setWidth(600);
    chartView->setMinimumSize(chartviewsize);
  //  chartView->chart()->setTheme(QChart::ChartThemeBlueNcs);
   // chartView->setStyleSheet("background-color: black; color: red;");


    // LED SETTINGS
    LED_ON.setText("Open COM4");
    FLICKER_LED.setText("Close COM4");
    LED_ON.setStyleSheet("padding: 3px; background-color: white; color: blue; border: 2px ridge black;");
    FLICKER_LED.setStyleSheet("padding: 3px; background-color: white; color: blue; border: 2px ridge black;");
    READ_BUTTON.setText("Clear Data");
    READ_BUTTON.setStyleSheet("padding: 3px; background-color: white; color: blue; border: 2px ridge black;");
    top_box_layout->addRow(com_button_layout);
    top_box_layout->addWidget(chartView);

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
