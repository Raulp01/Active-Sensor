#ifndef VIEWER
#define VIEWER

#include <QPushButton>
#include <QLabel>
#include "../Core/Container.h"
#include "MainWindow.h"

namespace View
{
    class Viewer : public QWidget
    {
        Q_OBJECT

        private:
        Core::Container& container;
        const Core::Sensor& sensor;
        MainWindow* mainwindow;
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
        Viewer(MainWindow* mainwindow, Core::Container& container, const Core::Sensor& sensor, QWidget* parent = 0);

        public slots:
        void deleteSensor();
        void simulateSensor();

        //Incompleta
        // connect editSensor
        // connect deleteSensor
    };
};

#endif