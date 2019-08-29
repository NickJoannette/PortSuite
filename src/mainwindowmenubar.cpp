#include "mainwindowmenubar.h"

MainWindowMenuBar::MainWindowMenuBar(QMainWindow* parent)
{
    // MENU BAR SETUP

        // ITEMS

       SubMenu_1 = new QMenu("");
      // MenuBar = new QMenuBar(parent);

       save_plot_action = new QAction("Save Plot",parent);
       export_data_action = new QAction("Export Data",parent);

       file_menu = new QMenu("File", parent);
       file_menu->setMinimumHeight(30);
       file_menu->addAction(save_plot_action);
       file_menu->addAction(export_data_action);

       choose_port_action = new QAction("Choose port...",parent);

       port_menu = new QMenu("Port", parent);
       port_menu->addAction(choose_port_action);

       addMenu(file_menu);
       addMenu(port_menu);

       // CUSTOMIZATION/ STYLES
      setStyleSheet
       ("QMenuBar::item:selected{background-color:green;}"

        "QMenu{background-color:black; color:white;"
        "border:1px solid  rgb(44,205,112);}"

        "QMenu::item{spacing: 3px; padding: 10px;}"
        "QMenu::item:selected{background-color: rgb(44,205,112);}"

        );

       setStyleSheet("background-color:black; "
                                      "border-bottom:1px solid darkgreen; "
                                      "color:white;"
                                      );

       addSeparator();



       // SETTING UP THE DIALOGS

       data_export_dialog = new ExportDialog();
       data_export_dialog->setMaximumHeight(200);



       // MENU CONNECTIONS

       QObject::connect(file_menu, SIGNAL(triggered(QAction*)), this, SLOT(EXPORT_DATA_CLICKED(QAction*)));


}

// MENU SLOTS

void MainWindowMenuBar::EXPORT_DATA_CLICKED(QAction* action)
{
    qDebug () << "Triggered: " << action->text();
    data_export_dialog->show();
}

