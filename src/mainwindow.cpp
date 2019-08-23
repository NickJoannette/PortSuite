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

    // CHART VIEW
     series = new QtCharts::QSplineSeries();
    QtCharts::QChart *chart;
    chart = new QtCharts::QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle("V");
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0,200);
    chart->axes(Qt::Vertical).first()->setRange(0, 1000);
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QSize chartviewsize;
    chartView->setStyleSheet("background_color: 2a4d10");
    chartviewsize.setHeight(350);
    chartviewsize.setWidth(600);
    chartView->setMinimumSize(chartviewsize);
    chartView->chart()->setTheme(QChart::ChartThemeDark);

    // LED SETTINGS
    LED_ON.setText("On/Off");
    FLICKER_LED.setText("Flicker the LED");
    LED_ON.setStyleSheet("padding: 3px; background-color: #505050; color: #ffffff; border: 2px ridge black;");
    FLICKER_LED.setStyleSheet("padding: 3px; background-color: #505050; color: #ffffff; border: 2px ridge black;");
    READ_BUTTON.setText("Read Wave");
    READ_BUTTON.setStyleSheet("padding: 3px; background-color: #505050; color: #e0e0e0; border: 2px ridge black;");
    top_box_layout->addWidget(&LED_ON);
    top_box_layout->addWidget(&FLICKER_LED);
    top_box_layout->addWidget(&READ_BUTTON);
    top_box_layout->addWidget(chartView);

    connect(&LED_ON,SIGNAL(clicked()),this,SLOT(LED_ONOFF_CLICKED()));
    connect(&FLICKER_LED,SIGNAL(clicked()),this,SLOT(FLICKER_LED_CLICKED()));
    connect(&READ_BUTTON,SIGNAL(clicked()),this,SLOT(READ_CLICKED()));

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
                           if (!qsp->isOpen()) qsp->open(QIODevice::WriteOnly);
                           s_com->qsp->write(QByteArray("A"));
                           s_com->sp->flush();

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
