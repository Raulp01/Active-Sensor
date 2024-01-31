#include "Viewer.h"
#include "ViewerVisitor.h"
#include "ChartVisitor.h"

namespace View
{
    Viewer::Viewer(std::vector<Core::Sensor*>& vector, Core::Sensor& sensor) : vector(vector), sensor(sensor)
    {
        layout = new QGridLayout(this);
        layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        simulate_sensor = new QPushButton("Simulate");
        layout->addWidget(simulate_sensor, 0, 2, 1, 1);
        connect(simulate_sensor, &QPushButton::pressed, this, &Viewer::simulateSensor);

        id = new QLabel("Id: " + QString::number(sensor.getId()));
        layout->addWidget(id, 1, 0, 1, 1);

        name = new QLabel("Name: " + QString::fromStdString(sensor.getName()));
        layout->addWidget(name, 1, 1, 1, 1);
        
        description = new QLabel("Description: " + QString::fromStdString(sensor.getDescription()));
        layout->addWidget(description, 2, 0, 1, 1);

        age = new QLabel("Age: " + QString::number(sensor.getAge()));
        layout->addWidget(age, 3, 0, 1, 1);

        height = new QLabel("Height: " + QString::number(sensor.getHeight(), 'f', 2));
        layout->addWidget(height, 4, 0, 1, 1);

        weight = new QLabel("Weight: " + QString::number(sensor.getWeight(), 'f', 2));
        layout->addWidget(weight, 4, 1, 1, 1);

        training_type = new QLabel("Training type: " + QString::fromStdString(sensor.getTrainingTypeToString()));
        layout->addWidget(training_type, 5, 0, 1, 1);
        
        training_time = new QLabel("Training time: " + QString::number(sensor.getTrainingTime(), 'f', 1));
        layout->addWidget(training_time, 5, 1, 1, 1);
    }

    void Viewer::simulateSensor()
    {
        sensor.setTimeChanged(false);
        sensor.simulate();
        this->show();
    }

    void Viewer::show()
    {
        ViewerVisitor visitor;
        sensor.accept(visitor);
        layout->addWidget(visitor.getWidget(), 6, 0);

        ChartVisitor chart;
        sensor.accept(chart);
        layout->addWidget(chart.getWidget(), 7, 0, Qt::AlignCenter);
    }
}