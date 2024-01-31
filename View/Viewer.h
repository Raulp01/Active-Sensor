#ifndef VIEWER
#define VIEWER

#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include "MainWindow.h"

namespace View
{
    class Viewer : public QWidget
    {
        Q_OBJECT

        private:
        std::vector<Core::Sensor*>& vector;
        Core::Sensor& sensor;
        QPushButton* simulate_sensor;
        QLabel* id;
        QLabel* name;
        QLabel* training_time;
        QLabel* training_type;
        QLabel* weight;
        QLabel* height;
        QLabel* description;
        QLabel* age;
        QGridLayout* layout;

        public:
        Viewer(std::vector<Core::Sensor*>& vector, Core::Sensor& sensor);
        void show();

        public slots:
        // void deleteSensor();
        void simulateSensor();

        //Incompleta
        // connect editSensor
        // connect deleteSensor
    };
}

#endif