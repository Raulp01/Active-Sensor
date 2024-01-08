#ifndef MAINWINDOW
#define MAINWINDOW

#include "../Core/Container.h"
#include "Scrollbar.h"
#include "Viewer.h"
#include <QMainWindow>
#include <QGridLayout>
// Include classi della GUI che compongono la Main Window

namespace View
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

        private:
        Core::Container& container;

        Scrollbar* scrollbar;
        QGridLayout* layout;
        Viewer* viewer;
        
        public:
        MainWindow(Core::Container& container);
        void openViewer(Core::Sensor& sensor);
    };
};

#endif