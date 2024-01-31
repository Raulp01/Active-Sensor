#include "Viewer.h"
#include "ViewerVisitor.h"
#include "ChartVisitor.h"
#include <QPushButton>
#include <QLabel>

namespace View
{
    Viewer::Viewer(std::vector<Core::Sensor*>& vector, Core::Sensor& sensor) : vector(vector), sensor(sensor)
    {
        layout = new QGridLayout(this);
        layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

        QPushButton* simulate_sensor = new QPushButton("Simulate");
        layout->addWidget(simulate_sensor, 1, 1, 1, 1);
        connect(simulate_sensor, &QPushButton::pressed, this, &Viewer::simulateSensor);

        QPushButton* reset_sensor = new QPushButton("Reset");
        layout->addWidget(reset_sensor, 1, 2, 1, 1);
        connect(reset_sensor, &QPushButton::pressed, this, &Viewer::reset);

        QLabel* id = new QLabel("Id: " + QString::number(sensor.getId()));
        layout->addWidget(id, 2, 1, 1, 1);

        QLabel* name = new QLabel("Name: " + QString::fromStdString(sensor.getName()));
        layout->addWidget(name, 2, 2, 1, 1);
        
        QLabel* description = new QLabel("Description: " + QString::fromStdString(sensor.getDescription()));
        layout->addWidget(description, 3, 1, 1, 1);

        QLabel* age = new QLabel("Age: " + QString::number(sensor.getAge()));
        layout->addWidget(age, 4, 1, 1, 1);

        QLabel* height = new QLabel("Height: " + QString::number(sensor.getHeight(), 'f', 2));
        layout->addWidget(height, 5, 1, 1, 1);

        QLabel* weight = new QLabel("Weight: " + QString::number(sensor.getWeight(), 'f', 2));
        layout->addWidget(weight, 5, 2, 1, 1);

        QLabel* training_type = new QLabel("Training type: " + QString::fromStdString(sensor.getTrainingTypeToString()));
        layout->addWidget(training_type, 6, 1, 1, 1);
        
        QLabel* training_time = new QLabel("Training time: " + QString::number(sensor.getTrainingTime(), 'f', 1));
        layout->addWidget(training_time, 6, 2, 1, 1);

        show();
    }

    void Viewer::simulateSensor()
    {
        sensor.setTimeChanged(false);
        sensor.simulate();
        this->show();
    }

    void Viewer::reset()
    {
        sensor.reset();
        this->show();
    }

    void Viewer::show()
    {
        ViewerVisitor visitor;
        sensor.accept(visitor);
        layout->addWidget(visitor.getWidget(), 7, 1);

        ChartVisitor chart;
        sensor.accept(chart);
        layout->addWidget(chart.getWidget(), 8, 1, 3, -1);
    }
}