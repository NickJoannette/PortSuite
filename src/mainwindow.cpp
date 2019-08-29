#include "mainwindow.h"
#include <QPushButton>
#include <QColor>
#include <iostream>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // MENU BAR SETUP
    // ITEMS
       m_pSubMenu = new QMenu("");
       QMenuBar* pMenuBar = new QMenuBar(this);
       setMenuBar(pMenuBar);

       save_plot_action = new QAction("Save Plot",this);
       export_data_action = new QAction("Export Data",this);
       file_menu = new QMenu("File", this);
       file_menu->setMinimumHeight(30);
       file_menu->addAction(save_plot_action);
       file_menu->addAction(export_data_action);
       choose_port_action = new QAction("Choose port...",this);
       port_menu = new QMenu("Port", this);
       port_menu->addAction(choose_port_action);

       this->menuBar()->addMenu(file_menu);
       this->menuBar()->addMenu(port_menu);




       // CUSTOMIZATION/ STYLES
       setStyleSheet
       ("QMenuBar::item:selected{background-color:green;}"

        "QMenu{background-color:black; color:white;"
        "border:1px solid  rgb(44,205,112);}"

        "QMenu::item{spacing: 3px; padding: 10px;}"
        "QMenu::item:selected{background-color: rgb(44,205,112);}"

        );

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


    // SETTING UP THE DIALOGS
       data_export_dialog = new QFileDialog(0,Qt::WindowStaysOnTopHint);
       data_export_dialog->setLabelText(QFileDialog::Accept, tr("Save"));
        data_export_dialog->setNameFilter(tr("Excel file (.xls .xlsx);;CSV file (.csv);;JSON file (.json)"));
        data_export_dialog->setViewMode(QFileDialog::List);
        data_export_dialog->setWindowTitle("Export data as...");
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

    com_button_layout = new QVBoxLayout(comControlWidget);

    transmission_label.setText("Transmission |");
    reception_label.setText("Reception |");


    com_button_layout->setSpacing(0);
    com_button_layout->addWidget(&OPEN_COM4);
    com_button_layout->addWidget(&FLICKER_LED);
    com_button_layout->addWidget(&READ_BUTTON);
    com_button_layout->addWidget(&RESET_DATA_BUTTON);
    com_button_layout->setSpacing(5);

    OPEN_COM4.setFixedSize(80,35);FLICKER_LED.setFixedSize(80,35);READ_BUTTON.setFixedSize(80,35);
    RESET_DATA_BUTTON.setFixedSize(80,35);

    // CHART VIEW

     QFont font;
     font.setPixelSize(24);

     // Setting and customizing the series plot
     series = new QtCharts::QSplineSeries();
     QColor darkgreen;
     darkgreen.setRgb(44,205,112);
     QPen pen(darkgreen);
     pen.setWidth(2);


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

    chartviewsize.setHeight(350);
    chartviewsize.setWidth(600);
    chartView->setMinimumSize(chartviewsize);

    // POST-THEME CUSTOMIZATIONS
    chartView->chart()->setTheme(QChart::ChartThemeDark);
     chartView->setStyleSheet("background-color: black;");
    series->setPen(pen);
    chart->setTitleBrush(QBrush(Qt::white));
    chart->setTitleFont(font);
    chart->setDropShadowEnabled();
    chart->setBackgroundRoundness(0);



    // BUTTON Customization

    OPEN_COM4.setText("Open Port");
    FLICKER_LED.setText("Close Port");
    OPEN_COM4.setStyleSheet(
                         "QPushButton:hover{background-color: green; } "
                         "QPushButton{padding: 3px; "
                         "background-color: black; color: white; "
                         "}"
                            );

    FLICKER_LED.setStyleSheet( "QPushButton:hover{background-color: green; } "
                               "QPushButton{padding: 3px; "
                               "background-color: black; color: white; "
                               " }"
                                 );

    READ_BUTTON.setText("Clear Graph");
    READ_BUTTON.setStyleSheet( "QPushButton:hover{background-color: green; } "
                               "QPushButton{padding: 3px; "
                               "background-color: black; color: white; "
                               " }"
                                 );

    RESET_DATA_BUTTON.setText("RESET DATA");
    RESET_DATA_BUTTON.setStyleSheet("QPushButton:hover{background-color: firebrick; } "
                                    "QPushButton{padding: 3px; "
                                    "background-color: maroon; color: white; "
                                    " }");

    // ADDING WIDGETS AND LAYOUTS TO MAIN LAYOUT


    top_box_layout->addWidget(chartView);

    //commsPanelWidget->setMaximumWidth(400);
        comms_panel_layout->addStretch(300);
    comms_panel_layout->addWidget(comControlWidget); comms_panel_layout->addWidget(&comms_log);
    //comms_panel_layout->setSizeConstraint(QLayout::SetMinimumSize);
    comms_panel_layout->addStretch(300);
    top_box_layout->addWidget(commsPanelWidget);

    connect(&OPEN_COM4,SIGNAL(clicked()),s_com,SLOT(Open_COM4()));
    connect(&OPEN_COM4,SIGNAL(clicked()),this,SLOT(OPEN_COM4_CLICKED()));

    connect(&FLICKER_LED,SIGNAL(clicked()),s_com,SLOT(Close_COM4()));
    connect(&FLICKER_LED,SIGNAL(clicked()),this,SLOT(CLOSE_COM4_CLICKED()));

    connect(&READ_BUTTON,SIGNAL(clicked()),this,SLOT(CLEAR_CHART_CLICKED()));
    connect(&RESET_DATA_BUTTON,SIGNAL(clicked()),this,SLOT(RESET_DATA_CLICKED()));
    connect(s_com,SIGNAL(send_chart_data(unsigned int, unsigned int)),this,SLOT(receive_chart_data(unsigned int, unsigned int)));


    // MENU CONNECTIONS
    connect(file_menu, SIGNAL(triggered(QAction*)), this, SLOT(EXPORT_DATA_CLICKED(QAction*)));
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
void MainWindow::OPEN_COM4_CLICKED()
{

    OPEN_COM4.setStyleSheet(
                               "QPushButton{padding: 3px; "
                               "background-color: green; color: white; "
                               "}"
                            );
    if (!s_com->qsp->isOpen())s_com->qsp->open(QIODevice::ReadOnly);
    if (s_com->qsp->isOpen()) comms_log.setText("Port Status: OPEN\n"
                                                "Bytes received: " + QString::number(total_bytes_read) +
                                                "\nMean value: "  + QString::number(average_data_value) +"\n");

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

void MainWindow::CLOSE_COM4_CLICKED()
{

     if (s_com->qsp->isOpen())s_com->qsp->close();
     if (!s_com->qsp->isOpen())
     {
         comms_log.setText("Port Status: CLOSED\n"
                           "Bytes received: " + QString::number(total_bytes_read) +
                           "\nMean value: "  + QString::number(average_data_value) +"\n");

         OPEN_COM4.setStyleSheet("QPushButton:hover{background-color: green; } "
          "QPushButton{padding: 3px; "
          "background-color: black; color: white; "
          "}");
     }

     /*  if (s_com->qsp->isOpen() && s_com->qsp->isWritable())
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

                }*/

}

void MainWindow::CLEAR_CHART_CLICKED()
{
   s_com->bytes_read = 0;
   series->clear();
   QString status = s_com->qsp->isOpen() ? "OPEN\n" : "CLOSED\n";
   comms_log.setText( "Port Status: " + status +
                     "Bytes received: " + QString::number(total_bytes_read) +
                     "\nMean value: "  + QString::number(average_data_value) +"\n");
}

void MainWindow::RESET_DATA_CLICKED()
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


// MENU SLOTS

void MainWindow::EXPORT_DATA_CLICKED(QAction* action)
{
    qDebug () << "Triggered: " << action->text();
    data_export_dialog->show();
}

