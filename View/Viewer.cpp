#include "Viewer.h"
#include "ViewerVisitor.h"
#include "ChartVisitor.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

namespace View
{
    Viewer::Viewer(std::vector<Core::Sensor*>& vector, Core::Sensor& sensor) : vector(vector), sensor(sensor)
    {
        std::cout << "Viewer::Viewer Costruttore Viewer vector = " << vector.size() << std::endl;

        QVBoxLayout* v_layout = new QVBoxLayout(this);
        v_layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QGridLayout* layout = new QGridLayout();
        layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);
        v_layout->addLayout(layout);

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

        QLabel* training_type = new QLabel("Training Type: " + QString::fromStdString(sensor.getTrainingTypeToString()));
        layout->addWidget(training_type, 6, 1, 1, 1);

        ViewerVisitor visitor;
        sensor.accept(visitor);
        v_layout->addWidget(visitor.getWidget());

        ChartVisitor chart_visitor;
        sensor.accept(chart_visitor);
        v_layout->addWidget(chart_visitor.getWidget());

        std::cout << "Viewer::Viewer dopo la creazione dei widget, prima del visitor" << std::endl;
        std::cout << "Viewer::Viewer chiama show" << std::endl;
    }

    void Viewer::simulateSensor()
    {
        std::cout << "Viewer::simulateSensor" << std::endl;
        sensor.setTimeChanged(false);
        sensor.simulate();
        emit showViewer(&sensor);
        std::cout << "Viewer::simulateSensor chiama show()" << std::endl;
    }

    void Viewer::reset()
    {
        std::cout << "Viewer::reset" << std::endl;
        sensor.reset();
        emit showViewer(&sensor);
    }
}