#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QtCharts>
#include <QtCharts/QAbstractAxis>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class MainWindow : public QWidget
{
    Q_OBJECT

public:

    MainWindow();
private slots:
    void LED_ONOFF_CLICKED();
    void FLICKER_LED_CLICKED();
private:


    QHBoxLayout * top_box_layout;
    QPushButton LED_ON;
    QPushButton FLICKER_LED;
    bool LED1_IS_ON = false;


    // SERIAL COMMUNICATIONS
    QSerialPort * qsp;

};



#endif // MAINWINDOW_H
