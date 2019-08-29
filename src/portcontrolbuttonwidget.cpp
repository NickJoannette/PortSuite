#include "portcontrolbuttonwidget.h"

PortControlButtonWidget::PortControlButtonWidget(SerialCommunicator* p)
{
    parent = p;

    QWidget *comControlWidget = new QWidget;
   // comControlWidget->setWindowFlag(Qt::FramelessWindowHint);
    comControlWidget->show();
    comControlWidget->resize(50,50);


    com_button_layout = new QVBoxLayout(comControlWidget);
    com_button_layout->setSpacing(0);
    com_button_layout->addWidget(&OPEN_COM4);
    com_button_layout->addWidget(&FLICKER_LED);
    com_button_layout->addWidget(&READ_BUTTON);
    com_button_layout->addWidget(&RESET_DATA_BUTTON);
    com_button_layout->setSpacing(5);

    OPEN_COM4.setFixedSize(80,35);
    FLICKER_LED.setFixedSize(80,35);
    READ_BUTTON.setFixedSize(80,35);
    RESET_DATA_BUTTON.setFixedSize(80,35);


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

    // CONNECTIONS

    connect(&OPEN_COM4,SIGNAL(clicked()),parent,SLOT(Open_COM4()));
    connect(&OPEN_COM4,SIGNAL(clicked()),this,SLOT(OPEN_COM4_CLICKED()));

    connect(&FLICKER_LED,SIGNAL(clicked()),parent,SLOT(Close_COM4()));
    connect(&FLICKER_LED,SIGNAL(clicked()),this,SLOT(CLOSE_COM4_CLICKED()));

    connect(&READ_BUTTON,SIGNAL(clicked()),this,SLOT(CLEAR_CHART_CLICKED()));
    connect(&RESET_DATA_BUTTON,SIGNAL(clicked()),this,SLOT(RESET_DATA_CLICKED()));

}

void PortControlButtonWidget::OPEN_COM4_CLICKED()
{

    OPEN_COM4.setStyleSheet(
                               "QPushButton{padding: 3px; "
                               "background-color: green; color: white; "
                               "}"
                            );

    if (!parent->qsp->isOpen())parent->qsp->open(QIODevice::ReadOnly);

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

     if (parent->qsp->isOpen())parent->qsp->close();
     if (!parent->qsp->isOpen())
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
    parent->bytes_read = 0;
    emit CLEAR_CLICKED();
}

void PortControlButtonWidget::RESET_DATA_CLICKED()
{
    emit RESET_CLICKED();
}



void PortControlButtonWidget::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void PortControlButtonWidget::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}



