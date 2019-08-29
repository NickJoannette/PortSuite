#ifndef PORTCONTROLBUTTONWIDGET_H
#define PORTCONTROLBUTTONWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "serialcommunicator.h"



class PortControlButtonWidget : public QDockWidget
{
    Q_OBJECT


public:
    PortControlButtonWidget(SerialCommunicator*);

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

    SerialCommunicator* parent;

    QVBoxLayout * com_button_layout;

    QPushButton OPEN_COM4;
    QPushButton FLICKER_LED;
    QPushButton READ_BUTTON;
    QPushButton RESET_DATA_BUTTON;
};

#endif // PORTCONTROLBUTTONWIDGET_H
