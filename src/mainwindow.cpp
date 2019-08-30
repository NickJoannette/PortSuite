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

    // TEST


    series0 = new QScatterSeries();
    series0->setName("scatter1");
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series0->setMarkerSize(15.0);

    QScatterSeries *series1 = new QScatterSeries();
    series1->setName("scatter2");
    series1->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    series1->setMarkerSize(20.0);

    QScatterSeries *series2 = new QScatterSeries();
    series2->setName("scatter3");
    series2->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    series2->setMarkerSize(30.0);

    //////////////

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
    chart->addSeries(series0);

    // Setting the Chart Title

    chart->setTitle("Galvanic Response");

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
    //setWindowFlag(Qt::FramelessWindowHint);

    // ADDING WIDGETS AND LAYOUTS TO MAIN LAYOUT

  //  addDockWidget(Qt::RightDockWidgetArea, pcbw);


   // pcbw->setFloating(true);
    QPoint mw = pos();
    int x = mw.x();
    int y =mw.y();
    pcbw->move(x-100,y-pcbw->height()+height()/2);
    top_box_layout->addWidget(chartView);
    top_box_layout->addWidget(&comms_log);

    QPixmap p = chartView->grab();
    QOpenGLWidget *glWidget  = chartView->findChild<QOpenGLWidget*>();
    if(glWidget){
        QPainter painter(&p);
        QPoint d = glWidget->mapToGlobal(QPoint())-chartView->mapToGlobal(QPoint());
        painter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
        painter.drawImage(d, glWidget->grabFramebuffer());
        painter.end();
    }

    p.save("a.png", "PNG");
    main_windows = this;
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
    series0->append(d,br);
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
