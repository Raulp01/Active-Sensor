#include "ViewerVisitor.h"
#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>

namespace View
{
    QWidget* ViewerVisitor::getWidget()
    {
        return widget;
    }

    void ViewerVisitor::visitCaloriesCounter(Core::CaloriesCounter& calories_counter)
    {
        QGridLayout* grid = new QGridLayout();
        grid->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

        QLabel* bpm = new QLabel("BPM: " + QString::number(calories_counter.getBpm()));
        grid->addWidget(bpm, 0, 0, 1, 1);

        QLabel* calories = new QLabel("Calories burned: " + QString::number(calories_counter.getCalories(), 'f', 2));
        grid->addWidget(calories, 0, 1, 1, 1);

        widget = new QWidget();
        widget->setLayout(grid);
    }
    
    void ViewerVisitor::visitActivity(Core::Activity& activity) 
    {
        QGridLayout* grid = new QGridLayout();
        grid->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

        QLabel* bpm = new QLabel("BPM: " + QString::number(activity.getBpm()));
        grid->addWidget(bpm, 0, 0, 1, 1);

        QLabel* calories = new QLabel("Calories burned: " + QString::number(activity.getCalories(), 'f', 2));
        grid->addWidget(calories, 0, 1, 1, 1);

        QLabel* distance = new QLabel("Distance: " + QString::number(activity.getDistance(), 'f', 2));
        grid->addWidget(distance, 1, 0, 1, 1);

        QLabel* speed = new QLabel("Avarage speed: " + QString::number(activity.getAvarageSpeed(), 'f', 2));
        grid->addWidget(speed, 1, 1, 1, 1);

        widget = new QWidget();
        widget->setLayout(grid);
    }

    void ViewerVisitor::visitHeartSensor(Core::HeartSensor& heart_sensor) 
    {
        QGridLayout* grid = new QGridLayout();
        grid->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

        QLabel* bpm = new QLabel("BPM: " + QString::number(heart_sensor.getBpm()));
        grid->addWidget(bpm, 0, 0, 1, 1);

        widget = new QWidget();
        widget->setLayout(grid);
    }
    
    void ViewerVisitor::visitSpeedometer(Core::Speedometer& speedometer) 
    {
        QGridLayout* grid = new QGridLayout();
        grid->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

        QLabel* distance = new QLabel("Distance: " + QString::number(speedometer.getDistance()));
        grid->addWidget(distance, 0, 0, 1, 1);

        QLabel* speed = new QLabel("Avarage speed: " + QString::number(speedometer.getAvarageSpeed()));
        grid->addWidget(speed, 0, 1, 1, 1);

        widget = new QWidget();
        widget->setLayout(grid);
    }
};