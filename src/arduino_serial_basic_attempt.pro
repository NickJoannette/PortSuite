#-------------------------------------------------
#
# Project created by QtCreator 2019-08-20T21:18:18
#
#-------------------------------------------------

QT += gui
QT += widgets
QT += charts
QT += serialport
QT += multimedia
# CONFIG += c++11 console

CONFIG -= app_bundle

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = arduino_serial_basic_attempt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        exportdialog.cpp \
        main.cpp \
        mainwindow.cpp \
        mainwindowmenubar.cpp \
        portcontrolbuttonwidget.cpp \
        serialcommunicator.cpp

HEADERS += \
        exportdialog.h \
        mainwindow.h \
        mainwindowmenubar.h \
        portcontrolbuttonwidget.h \
        serialcommunicator.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    s.mp3

RC_ICONS = serialcontrol.ico
