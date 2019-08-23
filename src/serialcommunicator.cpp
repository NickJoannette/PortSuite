#include "serialcommunicator.h"

SerialCommunicator(QtCharts::QSplineSeries* qss)
{
    series = qss;

    // SERIAL COMMUNICATIONS HANDLING
    qsp = new QSerialPort(this);
    QSerialPortInfo COM4("COM4");
    qsp->setPort(COM4);
    QIODevice::OpenMode mode(QIODevice::ReadOnly);
    qsp->open(QIODevice::ReadOnly);
    qsp->setBaudRate(QSerialPort::Baud9600);
    qsp->setDataBits(QSerialPort::Data8);
    qsp->setParity(QSerialPort::NoParity);
    qsp->setStopBits(QSerialPort::OneStop);
    qsp->setFlowControl(QSerialPort::NoFlowControl);



    connect(qsp, SIGNAL(readyRead()), this, SLOT(SERIAL_INTERACT()));
}

void SerialCommunicator::SERIAL_INTERACT()
{
    int len = 8;
    char * dat = new char[8]{" "};
     qsp->read(dat,len);
    std::string s = "";

    //if (dat[4] == '\r') qDebug() << dat[0] << dat[1] << dat[2] << dat[3] << dat[4] << dat[5] << dat[6]<< dat[7] << dat[8] << "\n------\n";
    for (int i = 0; i < 3; ++i)
    {
        s.push_back(dat[i]);    }
    int p;

 try{
   p = stoi(s);
   if (p>100){
       ++bytes_read;
       series->append(bytes_read,p);

            }

   } catch (std::invalid_argument & e) { return;}
}
