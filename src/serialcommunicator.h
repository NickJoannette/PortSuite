#ifndef SERIALCOMMUNICATOR_H
#define SERIALCOMMUNICATOR_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QtCharts>

class SerialCommunicator: public QWidget
{
    friend class MainWindow;
public:
    SerialCommunicator(QtCharts::QSplineSeries *);


private slots:

    void SERIAL_INTERACT();

protected:

    // SERIAL COMMUNICATIONS
    QtCharts::QSplineSeries* series;
    QSerialPort * qsp;
    QByteArray serialData;
    QString buffer;
    unsigned int bytes_read = 0;

};

#endif // SERIALCOMMUNICATOR_H
