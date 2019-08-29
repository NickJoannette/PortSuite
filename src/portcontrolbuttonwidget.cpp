#include "portcontrolbuttonwidget.h"


void PortControlButtonWidget::OPEN_COM4_CLICKED()
{

    OPEN_COM4.setStyleSheet(
                               "QPushButton{padding: 3px; "
                               "background-color: green; color: white; "
                               "}"
                            );

    if (!serial_parent->qsp->isOpen())serial_parent->qsp->open(QIODevice::ReadOnly);

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

void PortControlButtonWidget::CLOSE_COM4_CLICKED()
{

     if (serial_parent->qsp->isOpen())serial_parent->qsp->close();
     if (!serial_parent->qsp->isOpen())
     {
         OPEN_COM4.setStyleSheet("QPushButton:hover{background-color: green; } "
          "QPushButton{padding: 3px; "
          "background-color: black; color: white; "
          "}");
     }
    emit CLOSE_CLICKED();
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

void PortControlButtonWidget::CLEAR_CHART_CLICKED()
{
    serial_parent->bytes_read = 0;
    emit CLEAR_CLICKED();
}

void PortControlButtonWidget::RESET_DATA_CLICKED()
{
    emit RESET_CLICKED();
}




