#ifndef VIEWER
#define VIEWER

#include "Info.h"
#include <QPushButton>

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
        //id, training_type, training_time
        QLabel* id;
        QLabel* name;
        QLabel* training_time;
        QLabel* training__type;
        QLabel* weight;
        QLabel* height;
        QLabel* description;
        QLabel* age;

        public:
        Viewer(Core::Sensor& sensor, QWidget* parent = 0);
        void show();

        public slots:
        void simulateSensor();

        //Incompleta
    };
};

#endif