#include "MainWindow.h"

namespace View {

    MainWindow::MainWindow(Core::Container& container) : 
    container(container)
    {
        layout = new QGridLayout(this);
        layout->setAlignment(Qt::AlignCenter);

        scrollbar = new Scrollbar(this, container);
        layout->addWidget(scrollbar, 1, 0, 1, 1);
    }

    void MainWindow::openViewer(Core::Sensor& sensor)
    {
        viewer = new Viewer(this, container, sensor);
        layout->addWidget(viewer, 1, 0, 1, 3);
    }
};