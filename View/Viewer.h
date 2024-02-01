#ifndef VIEWER
#define VIEWER

#include "MainWindow.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

namespace View
{
    class Viewer : public QWidget
    {
        Q_OBJECT

        private:
        std::vector<Core::Sensor*>& vector;
        Core::Sensor& sensor;
        QGridLayout* layout;
        QVBoxLayout* v_layout;
        QWidget* visitor_widget;
        QWidget* chart_widget;
        QPushButton* simulate_sensor;
        QPushButton* reset_sensor;
        QLabel* id;
        QLabel* name;
        QLabel* description;
        QLabel* age;
        QLabel* height;
        QLabel* weight;
        QLabel* training_type;

        public:
        Viewer(std::vector<Core::Sensor*>& vector, Core::Sensor& sensor);
        void show();

        public slots:
        void simulateSensor();
        void reset();
    };
}

#endif