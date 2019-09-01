#ifndef PORTCONTROLBUTTONWIDGET_H
#define PORTCONTROLBUTTONWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "serialcommunicator.h"



class PortControlButtonWidget : public QWidget
{
    Q_OBJECT


public:
    PortControlButtonWidget(SerialCommunicator* serial_parent, QMainWindow* parent) : serial_parent(serial_parent){

                                                                                  QWidget *comControlWidget = new QWidget;

                                                                                  setStyleSheet("background: darkgreen;separator{background:darkgreen;}");
                                                                                  QLabel title;
                                                                                  title.setText("Port Control");
                                                                                  setWindowFlag(Qt::FramelessWindowHint);
                                                                                  setStyleSheet("background-color:#474747;");
                                                                                  setFixedWidth(100);
                                                                                  setFixedHeight(160);
                                                                                  com_button_layout = new QVBoxLayout(this);

                                                                                  com_button_layout->addWidget(&OPEN_COM4);
                                                                                  com_button_layout->addWidget(&FLICKER_LED);
                                                                                  com_button_layout->addWidget(&READ_BUTTON);
                                                                                  com_button_layout->addWidget(&RESET_DATA_BUTTON);
                                                                                  com_button_layout->setSpacing(5);

                                                                                  OPEN_COM4.setFixedSize(80,35);
                                                                                  FLICKER_LED.setFixedSize(80,35);
                                                                                  READ_BUTTON.setFixedSize(80,35);
                                                                                  RESET_DATA_BUTTON.setFixedSize(80,35);

                                                                                  show();

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

                                                                                  connect(&OPEN_COM4,SIGNAL(clicked()),serial_parent,SLOT(Open_COM4()));
                                                                                  connect(&OPEN_COM4,SIGNAL(clicked()),this,SLOT(OPEN_COM4_CLICKED()));

                                                                                  connect(&FLICKER_LED,SIGNAL(clicked()),serial_parent,SLOT(Close_COM4()));
                                                                                  connect(&FLICKER_LED,SIGNAL(clicked()),this,SLOT(CLOSE_COM4_CLICKED()));

                                                                                  connect(&READ_BUTTON,SIGNAL(clicked()),this,SLOT(CLEAR_CHART_CLICKED()));
                                                                                  connect(&RESET_DATA_BUTTON,SIGNAL(clicked()),this,SLOT(RESET_DATA_CLICKED()));}

    signals:
        void RESET_CLICKED();
        void CLOSE_CLICKED();
        void CLEAR_CLICKED();

private slots:
    void OPEN_COM4_CLICKED();
    void CLOSE_COM4_CLICKED();
    void CLEAR_CHART_CLICKED();
    void RESET_DATA_CLICKED();

private:

    SerialCommunicator* serial_parent;
    QMainWindow* parent;
    QVBoxLayout * com_button_layout;

    QPushButton OPEN_COM4;
    QPushButton FLICKER_LED;
    QPushButton READ_BUTTON;
    QPushButton RESET_DATA_BUTTON;
};

#endif // PORTCONTROLBUTTONWIDGET_H
