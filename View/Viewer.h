#ifndef VIEWER
#define VIEWER

#include "MainWindow.h"

namespace View
{
    class Viewer : public QWidget
    {
        Q_OBJECT

        private:
        std::vector<Core::Sensor*>& vector;
        Core::Sensor& sensor;

        public:
        Viewer(std::vector<Core::Sensor*>& vector, Core::Sensor& sensor);

        signals:
        void showViewer(Core::Sensor* view_sensor);

        public slots:
        void simulateSensor();
        void reset();
    };
}

#endif