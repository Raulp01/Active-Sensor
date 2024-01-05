#include "Viewer.h"
#include <QGridLayout>

namespace View
{
    Viewer::Viewer(Core::Sensor& sensor, QWidget* parent) : sensor(sensor), QWidget(parent)
    {
        QGridLayout* layout = new QGridLayout();
        layout->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

        edit_sensor = new QPushButton();
        layout->addWidget(edit_sensor, 0, 0, 1 ,1);
        // connect
        
        delete_sensor = new QPushButton();
        layout->addWidget(delete_sensor, 0, 1, 1, 1);
        // connect

        simulate_sensor = new QPushButton();
        layout->addWidget(simulate_sensor, 0, 2, 1, 1);
        connect(simulate_sensor, &QPushButton::pressed, this, &Viewer::simulateSensor);

        id = new QLabel();
        layout->addWidget(id, 1, 0, 1, 1);

        name = new QLabel();
        layout->addWidget(name, 1, 1, 1, 1);
        
        description = new QLabel();
        layout->addWidget(description, 2, 0, 2, 2);

        age = new QLabel();
        layout->addWidget(age, 3, 0, 1, 1);

        height = new QLabel();
        layout->addWidget(height, 4, 0, 1, 1);

        weight = new QLabel();
        layout->addWidget(weight, 4, 1, 1, 1);

        training__type = new QLabel();
        layout->addWidget(training__type, 5, 0, 1, 1);
        
        training_time = new QLabel();
        layout->addWidget(training_time, 5, 1, 1, 1);

        /*
        ViewerVisitor visitor;
        sensor.accept(visitor);
        layout->addWidget(visitor.getWidget(), 6, 0);
        */
    }

    void show()
    {
        //SetText
    }

    void Viewer::simulateSensor()
    {
        sensor.simulate();
        this->show();
    }
}