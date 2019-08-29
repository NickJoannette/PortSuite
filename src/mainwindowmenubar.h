#ifndef MAINWINDOWMENUBAR_H
#define MAINWINDOWMENUBAR_H
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QtWidgets>
#include <QWidget>
#include "exportdialog.h"

class MainWindowMenuBar : public QMenuBar
{
       Q_OBJECT
public:


    MainWindowMenuBar(QMainWindow* parent);
    //QMenuBar* menuBar(){return MenuBar;}

private:
    // MENU
    QMenu* file_menu;
    QMenu* port_menu;
    QAction *save_plot_action, *export_data_action;
    QAction *choose_port_action;
    QMenu* SubMenu_1;
    //QMenuBar* MenuBar;

    // MENU DIALOGS
    ExportDialog* data_export_dialog;

private slots:
        void EXPORT_DATA_CLICKED(QAction* action);

};

#endif // MAINWINDOWMENUBAR_H
