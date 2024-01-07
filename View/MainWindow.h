#ifndef MAINWINDOW
#define MAINWINDOW

#include "../Core/Container.h"
#include <QMainWindow>
#include "Viewer.h"
// Include classi della GUI che compongono la Main Window

namespace View
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

        private:
        Core::Activity& activity;
        
        public:
        MainWindow(Core::Activity& activity);
    };
};

#endif