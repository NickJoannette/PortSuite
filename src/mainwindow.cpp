#include "mainwindow.h"
#include <QPushButton>
#include <QColor>
#include <iostream>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // MENU BAR SETUP
       m_pSubMenu = NULL;
       QMenuBar* pMenuBar = new QMenuBar(this);

       setMenuBar(pMenuBar);

       save_plot_action = new QAction("Save Plot",this);
       setStyleSheet
       ("QMenu{background-color:black; color:white;"
        "border:1px solid  rgb(44,205,112);}"

        "QMenu::item{spacing: 3px; padding: 10px;}"
        "QMenu::item:selected{background-color: rgb(44,205,112);}"
        );

       export_data_action = new QAction("Export Data", this);
       menu = new QMenu("File", this);
       menu->addAction(save_plot_action);
       menu->addAction(export_data_action);
       this->menuBar()->addMenu(menu);




       this->menuBar()->setStyleSheet("background-color:black; "
                                      "border-bottom:1px solid darkgreen; "
                                      "color:white;"
                                      );

       this->menuBar()->addSeparator();

    // SERIAL COMM
    s_com = new SerialCommunicator(series);

    // STYLE AND MAIN LAYOUT


    QWidget *topWidget = new QWidget;
    topWidget->setStyleSheet("background-color:#474747;");
    QWidget *comControlWidget = new QWidget;
    top_box_layout = new QVBoxLayout(topWidget);
    top_box_layout ->setSpacing(5);
    topWidget->setLayout(top_box_layout);


    setCentralWidget(topWidget);

    // COMMS Customization

    QWidget *commsPanelWidget = new QWidget;
    comms_panel_layout = new QHBoxLayout(commsPanelWidget);

    // Setting comms log and other static memory member widgets' properties

    comms_log.setStyleSheet("padding:5px; font-size: 12px; color: white; background-color: black; border:1px solid  rgb(44,205,112);");
    comms_log.setText("Bytes received: " + QString::number(total_bytes_read) + "\nMean value:\n");

    comms_log.setFixedSize(150,80);
    comms_panel_layout->setSpacing(0);


    QSpacerItem height_spacer_100(100,100);
    com_button_layout = new QVBoxLayout(comControlWidget);

    transmission_label.setText("Transmission |");
    reception_label.setText("Reception |");


    com_button_layout->setSpacing(0);
    com_button_layout->addWidget(&OPEN_COM4);
    com_button_layout->addWidget(&FLICKER_LED);
    com_button_layout->addWidget(&READ_BUTTON);
    com_button_layout->addWidget(&RESET_DATA_BUTTON);

    OPEN_COM4.setFixedSize(80,35);FLICKER_LED.setFixedSize(80,35);READ_BUTTON.setFixedSize(80,35);
    RESET_DATA_BUTTON.setFixedSize(80,35);

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
    chartView->setStyleSheet("background-color: black");
    chartviewsize.setHeight(350);
    chartviewsize.setWidth(600);
    chartView->setMinimumSize(chartviewsize);

    // POST-THEME CUSTOMIZATIONS
    chartView->chart()->setTheme(QChart::ChartThemeDark);
    chart->setTitleBrush(QBrush(Qt::white));
    chart->setTitleFont(font);

    // BUTTON Customization
    OPEN_COM4.setText("Open COM4");
    FLICKER_LED.setText("Close COM4");
    OPEN_COM4.setStyleSheet("padding: 3px; "
                         "background-color: black; color: white; "
                         "border:1px solid  rgb(44,205,112); "
                            );

    FLICKER_LED.setStyleSheet("padding: 3px; "
                              "background-color: black; color: white; "
                              "border:1px solid  rgb(44,205,112); "
                                 );

    READ_BUTTON.setText("Clear Graph");
    READ_BUTTON.setStyleSheet("padding: 3px; "
                              "background-color: black; color: white; "
                              "border:1px solid  rgb(44,205,112); "
                                 );

    RESET_DATA_BUTTON.setText("RESET DATA");
    RESET_DATA_BUTTON.setStyleSheet("padding: 3px; "
                                    "font-weight: 2px;"
                              "background-color: darkgreen;"
                              " color: white;"

                              "border: 1px solid darkgrey;");

    // ADDING WIDGETS AND LAYOUTS TO MAIN LAYOUT


    top_box_layout->addWidget(chartView);
    comControlWidget->setMaximumWidth(200);
    comms_panel_layout->addWidget(comControlWidget); comms_panel_layout->addWidget(&comms_log);
    top_box_layout->addWidget(commsPanelWidget);

    connect(&OPEN_COM4,SIGNAL(clicked()),s_com,SLOT(Open_COM4()));
    connect(&FLICKER_LED,SIGNAL(clicked()),s_com,SLOT(Close_COM4()));
    connect(&READ_BUTTON,SIGNAL(clicked()),this,SLOT(CLEAR_CHART_CLICKED()));
    connect(&RESET_DATA_BUTTON,SIGNAL(clicked()),this,SLOT(RESET_DATA_CLICKED()));
    connect(s_com,SIGNAL(send_chart_data(unsigned int, unsigned int)),this,SLOT(receive_chart_data(unsigned int, unsigned int)));
}


void MainWindow::receive_chart_data(unsigned int br, unsigned int d)
{
    qDebug() << "Received: " << br << ", " << d << "\n";
    total_bytes_read+=1;
    series->append(br, d);
    data_value_sum+=d;
    average_data_value = data_value_sum/total_bytes_read;
    comms_log.setText("Bytes received: " + QString::number(total_bytes_read) +
                      "\nMean value: "  + QString::number(average_data_value) +"\n");
}
void MainWindow::OPEN_COM4_CLICKED()
{
    if (!s_com->qsp->isOpen())s_com->qsp->open(QIODevice::ReadOnly);
/*
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
                }*/

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

void MainWindow::CLEAR_CHART_CLICKED()
{
   s_com->bytes_read = 0;
   series->clear();
   comms_log.setText("Bytes received: " + QString::number(total_bytes_read) +
                     "\nMean value: "  + QString::number(average_data_value) +"\n");
}

void MainWindow::RESET_DATA_CLICKED()
{
  // chartView->chart()->setTheme(QChart::ChartThemeDark);
   total_bytes_read = 0;
   data_value_sum = 0;
   average_data_value = 0;
   comms_log.setText("Bytes received: " + QString::number(total_bytes_read) +
                     "\nMean value: "  + QString::number(average_data_value) +"\n");

}



