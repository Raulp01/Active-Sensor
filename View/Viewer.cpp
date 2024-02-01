#include "Viewer.h"
#include "ViewerVisitor.h"
#include "ChartVisitor.h"

namespace View
{
    Viewer::Viewer(std::vector<Core::Sensor*>& vector, Core::Sensor& sensor) : vector(vector), sensor(sensor)
    {
        std::cout << "Viewer::Viewer Costruttore Viewer vector = " << vector.size() << std::endl;

        v_layout = new QVBoxLayout(this);
        v_layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        layout = new QGridLayout();
        layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);
        v_layout->addLayout(layout);

        simulate_sensor = new QPushButton();
        layout->addWidget(simulate_sensor, 1, 1, 1, 1);
        connect(simulate_sensor, &QPushButton::pressed, this, &Viewer::simulateSensor);

        reset_sensor = new QPushButton();
        layout->addWidget(reset_sensor, 1, 2, 1, 1);
        connect(reset_sensor, &QPushButton::pressed, this, &Viewer::reset);

        id = new QLabel();
        layout->addWidget(id, 2, 1, 1, 1);

        name = new QLabel();
        layout->addWidget(name, 2, 2, 1, 1);
        
        description = new QLabel();
        layout->addWidget(description, 3, 1, 1, 1);

        age = new QLabel();
        layout->addWidget(age, 4, 1, 1, 1);

        height = new QLabel();
        layout->addWidget(height, 5, 1, 1, 1);

        weight = new QLabel();
        layout->addWidget(weight, 5, 2, 1, 1);

        training_type = new QLabel();
        layout->addWidget(training_type, 6, 1, 1, 1);

        this->show();

        std::cout << "Viewer::Viewer dopo la creazione dei widget, prima del visitor" << std::endl;
        std::cout << "Viewer::Viewer chiama show" << std::endl;
    }

    void Viewer::simulateSensor()
    {
        std::cout << "Viewer::simulateSensor" << std::endl;
        sensor.setTimeChanged(false);
        sensor.simulate();
        this->show();
    }

    void Viewer::reset()
    {
        std::cout << "Viewer::reset" << std::endl;
        sensor.reset();
        this->show();
    }

    void Viewer::show()
    {
        std::cout << "Viewer::show" << std::endl;

        simulate_sensor->setText("Simulate");
        reset_sensor->setText("Reset");
        id->setText("Id: " + QString::number(sensor.getId()));
        name->setText("Name: " + QString::fromStdString(sensor.getName()));
        description->setText("Description: " + QString::fromStdString(sensor.getDescription()));
        age->setText("Age: " + QString::number(sensor.getAge()));  
        height->setText("Height: " + QString::number(sensor.getHeight(), 'f', 2));
        weight->setText("Weight: " + QString::number(sensor.getWeight(), 'f', 2));
        training_type->setText("Training Type: " + QString::fromStdString(sensor.getTrainingTypeToString()));
        

        if(visitor_widget != nullptr)
        {
            std::cout << "Viewer::show visitor_widget!= nullptr" << std::endl;
            v_layout->removeWidget(visitor_widget);
            visitor_widget = new QWidget();
        }
        if(chart_widget!= nullptr)
        {
            std::cout << "Viewer::show chart_widget != nullptr" << std::endl;
            v_layout->removeWidget(chart_widget);
            chart_widget = new QWidget();
        }
        std::cout << "Viewer::show visitor_widget == nullptr && chart_widget == nullptr" << std::endl;
        ViewerVisitor visitor;
        sensor.accept(visitor);
        visitor_widget = visitor.getWidget();
        v_layout->addWidget(visitor_widget);

        ChartVisitor chart_visitor;
        sensor.accept(chart_visitor);
        chart_widget = chart_visitor.getWidget();
        v_layout->addWidget(chart_widget);
    }
}