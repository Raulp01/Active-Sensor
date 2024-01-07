#ifndef VIEWER
#define VIEWER

#include <QPushButton>
#include <QLabel>
#include "../Core/Activity.h"

namespace View
{
    class Viewer : public QWidget
    {
        Q_OBJECT

        private:
        Core::Sensor& sensor;
        QPushButton* edit_sensor;
        QPushButton* delete_sensor;
        QPushButton* simulate_sensor;
        QLabel* id;
        QLabel* name;
        QLabel* training_time;
        QLabel* training_type;
        QLabel* weight;
        QLabel* height;
        QLabel* description;
        QLabel* age;

        public:
        Viewer(Core::Sensor& sensor, QWidget* parent = 0);

        public slots:
        void simulateSensor();

        //Incompleta
        // connect editSensor
        // connect deleteSensor
    };
};

#endif