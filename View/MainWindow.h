#ifndef MAINWINDOW
#define MAINWINDOW

#include "../Core/Container.h"
#include <QWidget>
#include <QGridLayout>
// Include classi della GUI che compongono la Main Window

namespace View
{
    class MainWindow : public QWidget
    {
        Q_OBJECT
        private:
        Core::Container& container;
        
        public:
        MainWindow(Core::Container& container, QWidget* parent = 0);
    };
};

#endif