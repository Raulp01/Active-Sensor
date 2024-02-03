#ifndef VIEWER
#define VIEWER

#include "MainWindow.h"

namespace View
{
    class Viewer : public QWidget
    {
        Q_OBJECT

        private:
        Core::Sensor& sensor;

        public:
        Viewer(Core::Sensor& sensor);

        signals:
        void reloadViewer(Core::Sensor* view_sensor);

        public slots:
        void simulateSensor();
        void reset();
    };
}

#endif