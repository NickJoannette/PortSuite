#include "mainwindowmenubar.h"

MainWindowMenuBar::MainWindowMenuBar(MainWindow* parent)
{
    // MENU BAR SETUP

        // ITEMS

       SubMenu_1 = new QMenu("");
      // MenuBar = new QMenuBar(parent);
       new_window_action = new QAction("Extra Window");
       save_plot_action = new QAction("Save Plot",parent);
       export_data_action = new QAction("Export Data",parent);

       file_menu = new QMenu("File", parent);
       file_menu->setMinimumHeight(30);
       file_menu->addAction(new_window_action);
       file_menu->addAction(save_plot_action);
       file_menu->addAction(export_data_action);

       choose_port_action = new QAction("Choose port...",parent);

       port_menu = new QMenu("Port", parent);
       port_menu->addAction(choose_port_action);
       data_export_dialog = new ExportDialog();
       data_export_dialog->setMaximumHeight(200);
       addMenu(file_menu);
       addMenu(port_menu);

       // CUSTOMIZATION/ STYLES
        parent->setStyleSheet
       ("QMenuBar::item:selected{background-color:green;}"
        "QMenuBar{background-color:black; "
                                           "border-bottom:1px solid darkgreen; "
                                           "color:white;}"
        "QMenu{background-color:black; color:white;"
        "border:1px solid  rgb(44,205,112);}"

        "QMenu::item{spacing: 3px; padding: 10px;}"
        "QMenu::item:selected{background-color: rgb(44,205,112);}"
        "QMainWindow::separator{background: blue;}"
        );


        ExportDialog* save_file_dialog = new ExportDialog();


       // MENU CONNECTIONS

       QObject::connect(file_menu, SIGNAL(triggered(QAction*)), this, SLOT(EXPORT_DATA_CLICKED(QAction*)));


}

// MENU SLOTS

#include <ctime>
#include <chrono>

  std::string timeWithCTimeS()
  {
    char buffer[26];
        rsize_t buffersize = 26;
        std::time_t current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        ctime_s(buffer, buffersize, &current_time);
    return buffer;
 }
void MainWindowMenuBar::EXPORT_DATA_CLICKED(QAction* action)
{
    qDebug () << "Triggered: " << action->text();

    if (action->text() == "Export Data")
    {
        qDebug() << QString::fromStdString(timeWithCTimeS());
        data_export_dialog->show();
    }

    else if (action->text() == "Save Plot")
    {
        QPixmap p;
        QOpenGLWidget *glWidget  = parent->chartView->findChild<QOpenGLWidget*>();

        if(glWidget){
            QPainter painter(&p);
            QPoint d = glWidget->mapToGlobal(QPoint())-parent->chartView->mapToGlobal(QPoint());
            painter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
            painter.drawImage(d, glWidget->grabFramebuffer());
            painter.end();
        }
           save_file_dialog->show();
        QString s = save_file_dialog->getSaveFileName();
        p.save("a.png", "PNG");
    }

    else if (action->text() == "Extra Window")
    {
        main_windows = new MainWindow(this);
        main_windows->setWindowTitle("Heart Response");
        main_windows->chartView->chart()->setTitle("Signal");
        main_windows->show();
    }


}

