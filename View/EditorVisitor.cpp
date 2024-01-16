#include "EditorVisitor.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>

namespace View
{
    QWidget* EditorVisitor::getWidget()
    {
        return widget;
    }

    void EditorVisitor::visitHeartSensor(Core::HeartSensor* heart_sensor) 
    {
        layout->setAlignment(Qt::AlignCenter);

        QLabel* label = new QLabel("No more parameters are required");
        layout->addWidget(label);

        widget = new QWidget();
        widget->setLayout(layout);
    }

    void EditorVisitor::visitCaloriesCounter(Core::CaloriesCounter* calories) 
    {
        layout->setAlignment(Qt::AlignCenter);

        QLabel* label = new QLabel("No more parameters are required");
        layout->addWidget(label);

        widget = new QWidget();
        widget->setLayout(layout);
    }
    
    void EditorVisitor::visitSpeedometer(Core::Speedometer* speedometer)
    {
        layout->setAlignment(Qt::AlignCenter);

        QFormLayout* form_distance = new QFormLayout();
        form_distance->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

        distance = new QDoubleSpinBox();
        distance->setMinimum(0);
        distance->setSingleStep(0.5);
        distance->setValue(speedometer->getDistance());
        form_distance->addRow("Distance:", distance);

        layout->addLayout(form_distance);

        widget = new QWidget();
        widget->setLayout(layout);
    }

    void EditorVisitor::visitActivity(Core::Activity* activity)
    {
        layout->setAlignment(Qt::AlignCenter);

        QFormLayout* form_distance = new QFormLayout();
        form_distance->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

        distance = new QDoubleSpinBox();
        distance->setMinimum(0);
        distance->setSingleStep(0.5);
        distance->setValue(activity->getDistance());
        form_distance->addRow("Distance:", distance);

        layout->addLayout(form_distance);

        widget = new QWidget();
        widget->setLayout(layout);
    }

    void EditorVisitor::editSpeedometer(Core::Speedometer* speedometer)
    {
        speedometer->setDistance(distance->value());

        this->close();
    }

    void EditorVisitor::editActivity(Core::Activity* activity)
    {
        activity->setDistance(distance->value());

        this->close();
    }
}