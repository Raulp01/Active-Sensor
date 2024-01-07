#include "MainWindow.h"

namespace View {

    MainWindow::MainWindow(Core::Activity& activity) : activity(activity) 
    {
        Viewer* viewer = new Viewer(activity);
        setCentralWidget(viewer);
    }

};