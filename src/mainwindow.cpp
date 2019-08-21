#include "mainwindow.h"
#include <QPushButton>
#include <QColor>

MainWindow::MainWindow()
{
    setStyleSheet("background-color: lightgrey");
    QWidget *topWidget = new QWidget;
    top_box_layout = new QHBoxLayout(topWidget);
    setLayout(top_box_layout);


    LED_ON.setText("On/Off");
    FLICKER_LED.setText("Flicker the LED");
    LED_ON.setStyleSheet("padding: 3px; background-color: #505050; color: #ffffff; border: 2px ridge black;");
    FLICKER_LED.setStyleSheet("padding: 3px; background-color: #505050; color: #ffffff; border: 2px ridge black;");
    top_box_layout->addWidget(&LED_ON);
    top_box_layout->addWidget(&FLICKER_LED);

    // SERIAL COMMUNICATIONS HANDLING
    qsp = new QSerialPort();
    QSerialPortInfo COM4("COM4");
    qsp->setPort(COM4);
    QIODevice::OpenMode mode(QIODevice::ReadWrite);
    qsp->open(QIODevice::WriteOnly);
               qsp->setBaudRate(QSerialPort::Baud9600);
               qsp->setDataBits(QSerialPort::Data8);
               qsp->setParity(QSerialPort::NoParity);
               qsp->setStopBits(QSerialPort::OneStop);
               qsp->setFlowControl(QSerialPort::NoFlowControl);

    connect(&LED_ON,SIGNAL(clicked()),this,SLOT(LED_ONOFF_CLICKED()));
    connect(&FLICKER_LED,SIGNAL(clicked()),this,SLOT(FLICKER_LED_CLICKED()));
}

void MainWindow::LED_ONOFF_CLICKED()
{
    if (!qsp->isOpen())qsp->open(QIODevice::WriteOnly);

    if (qsp->isOpen() && qsp->isWritable())
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

                    qsp->write(*ba);
                    qsp->flush();
                    qsp->close();
                }

}

void MainWindow::FLICKER_LED_CLICKED()
{
     if (!qsp->isOpen())qsp->open(QIODevice::WriteOnly);

     if (qsp->isOpen() && qsp->isWritable())
                {
                        for (int i = 0; i < 10; ++i)
                        {
                           if (!qsp->isOpen()) qsp->open(QIODevice::WriteOnly);
                           qsp->write(QByteArray("A"));
                           qsp->flush();

                           qsp->close();
                           QThread::msleep(25);
                           qsp->open(QIODevice::WriteOnly);
                           qsp->write(QByteArray("B"));
                           qsp->flush();

                           qsp->close();
                           QThread::msleep(25);

                        }

                }

}
