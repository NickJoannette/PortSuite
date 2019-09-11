#include "serialcommunicator.h"

SerialCommunicator::SerialCommunicator(QtCharts::QSplineSeries* qss)
{
    series = qss;

    // SERIAL COMMUNICATIONS HANDLING
    qsp = new QSerialPort(this);
    QSerialPortInfo COM4("COM4");
    qsp->setPort(COM4);

    connect(qsp, SIGNAL(readyRead()), this, SLOT(SERIAL_INTERACT()));
}

void SerialCommunicator::SERIAL_INTERACT()
{
    unsigned int len = 8;
    char * dat = new char[8]{" "};
    qsp->read(dat,len);
    std::string s = "";

    for (unsigned int i = 0; i < 3; ++i) s.push_back(dat[i]);
    unsigned int p;

    try{
        // This is configured for a sensor which communicates voltage values between 400 and 800; eliminating values less than
        // 100 gets rid of anomalies
           p = stoi(s);
           if (p>100){
           ++bytes_read;
           emit(send_chart_data(bytes_read, p));

       }
   } catch (std::invalid_argument & e) { return;}
}


void SerialCommunicator::Open_COM4()
{
    QIODevice::OpenMode mode(QIODevice::ReadOnly);

    qsp->open(QIODevice::ReadOnly);
    qsp->setBaudRate(QSerialPort::Baud9600);
    qsp->setDataBits(QSerialPort::Data8);
    qsp->setParity(QSerialPort::NoParity);
    qsp->setStopBits(QSerialPort::OneStop);
    qsp->setFlowControl(QSerialPort::NoFlowControl);
}

void SerialCommunicator::Close_COM4()
{
    qsp->flush();
    qsp->close();
}
