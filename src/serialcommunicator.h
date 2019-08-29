#ifndef SERIALCOMMUNICATOR_H
#define SERIALCOMMUNICATOR_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QtCharts>

class PortControlButtonWidget;

class SerialCommunicator: public QWidget
{
    Q_OBJECT

    friend class PortControlButtonWidget;
    friend class MainWindow;

public:
    SerialCommunicator(QtCharts::QSplineSeries *);

signals:
  void send_chart_data(unsigned int, unsigned int);

private slots:

    void SERIAL_INTERACT();
    void Open_COM4();
    void Close_COM4();

protected:

    // SERIAL COMMUNICATIONS

    QtCharts::QSplineSeries* series;
    QSerialPort * qsp;
    QByteArray serialData;
    QString buffer;
    unsigned int bytes_read = 0;

};

#endif // SERIALCOMMUNICATOR_H
