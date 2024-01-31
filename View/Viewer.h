#ifndef VIEWER
#define VIEWER

#include "MainWindow.h"
#include <QGridLayout>

namespace View
{
    class Viewer : public QWidget
    {
        Q_OBJECT

        private:
        std::vector<Core::Sensor*>& vector;
        Core::Sensor& sensor;
        QGridLayout* layout;

        public:
        Viewer(std::vector<Core::Sensor*>& vector, Core::Sensor& sensor);
        void show();

        public slots:
        void simulateSensor();
        void reset();
    };
}

#endif