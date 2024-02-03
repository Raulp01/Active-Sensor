#include "Viewer.h"
#include "ViewerVisitor.h"
#include "ChartVisitor.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

namespace View
{
    Viewer::Viewer(Core::Sensor& sensor) : sensor(sensor)
    {
        QVBoxLayout* v_layout = new QVBoxLayout(this);

        QGridLayout* layout = new QGridLayout();
        layout->setAlignment(Qt::AlignCenter | Qt::AlignLeft);
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

        QFrame* line = new QFrame();
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        v_layout->addWidget(line);

        // Visitor per i dettagli del sensore non disponibili in Sensor
        ViewerVisitor visitor;
        sensor.accept(visitor);
        v_layout->addWidget(visitor.getWidget());

        // Creazione del grafico
        ChartVisitor chart_visitor;
        sensor.accept(chart_visitor);
        v_layout->addWidget(chart_visitor.getWidget());
    }

    // Reimposta sensor per la prossima simulazione, simula e ricostruisce il viewer
    void Viewer::simulateSensor()
    {
        sensor.setTimeChanged(false);
        sensor.simulate();
        emit reloadViewer(&sensor);
    }

    // Resetta i valori del sensore
    void Viewer::reset()
    {
        sensor.reset();
        emit reloadViewer(&sensor);
    }
}