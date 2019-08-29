#ifndef PORTCONTROLBUTTONWIDGET_H
#define PORTCONTROLBUTTONWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "serialcommunicator.h"



class PortControlButtonWidget : public QDockWidget
{
    Q_OBJECT


public:
    PortControlButtonWidget(SerialCommunicator* serial_parent, QMainWindow* parent) : QDockWidget(parent), serial_parent(serial_parent){


                                                                                  QWidget *comControlWidget = new QWidget;

                                                                                  setWidget(comControlWidget);
                                                                                  setStyleSheet("background-color:black;");
                                                                                  setAttribute(Qt::WA_TranslucentBackground, false);
                                                                                  setAttribute(Qt::WA_NoSystemBackground, false);
                                                                                  comControlWidget->show();
                                                                                  comControlWidget->setStyleSheet("background-color:#474747;");
                                                                                  comControlWidget->setFixedWidth(95);
                                                                                  comControlWidget->setFixedHeight(160);
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
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;

    SerialCommunicator* serial_parent;
    QMainWindow* parent;
    QVBoxLayout * com_button_layout;

    QPushButton OPEN_COM4;
    QPushButton FLICKER_LED;
    QPushButton READ_BUTTON;
    QPushButton RESET_DATA_BUTTON;
};

#endif // PORTCONTROLBUTTONWIDGET_H
