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
        widget = new QWidget();

        QGridLayout* grid = new QGridLayout();
        widget->setLayout(grid);
        grid->setAlignment(Qt::AlignTop | Qt::AlignCenter);

        QLabel* training_time = new QLabel("Training time: " + QString::number(calories_counter.getTrainingTime(), 'f', 1));
        grid->addWidget(training_time, 1, 1, 1, 1);

        QLabel* bpm = new QLabel("BPM: " + QString::number(calories_counter.getBpm()));
        grid->addWidget(bpm, 2, 1, 1, 1);

        QLabel* calories = new QLabel("Calories burned: " + QString::number(calories_counter.getCalories(), 'f', 2));
        grid->addWidget(calories, 2, 2, 1, 1);
    }
    
    void ViewerVisitor::visitActivity(Core::Activity& activity) 
    {
        widget = new QWidget();

        QGridLayout* grid = new QGridLayout();
        widget->setLayout(grid);
        grid->setAlignment(Qt::AlignTop | Qt::AlignCenter);

        QLabel* training_time = new QLabel("Training time: " + QString::number(activity.getTrainingTime(), 'f', 2));
        grid->addWidget(training_time, 1, 1, 1, 1);

        QLabel* bpm = new QLabel("BPM: " + QString::number(activity.getBpm()));
        grid->addWidget(bpm, 2, 1, 1, 1);

        QLabel* calories = new QLabel("Calories burned: " + QString::number(activity.getCalories(), 'f', 2));
        grid->addWidget(calories, 2, 2, 1, 1);

        QLabel* distance = new QLabel("Distance: " + QString::number(activity.getDistance(), 'f', 2));
        grid->addWidget(distance, 3, 1, 1, 1);

        QLabel* speed = new QLabel("Avarage speed: " + QString::number(activity.getSpeed(), 'f', 2));
        grid->addWidget(speed, 3, 2, 1, 1);
    }

    void ViewerVisitor::visitHeartSensor(Core::HeartSensor& heart_sensor) 
    {
        widget = new QWidget();
        QGridLayout* grid = new QGridLayout();
        widget->setLayout(grid);
        grid->setAlignment(Qt::AlignTop | Qt::AlignCenter);

        QLabel* training_time = new QLabel("Training time: " + QString::number(heart_sensor.getTrainingTime(), 'f', 2));
        grid->addWidget(training_time, 1, 1, 1, 1);

        QLabel* bpm = new QLabel("BPM: " + QString::number(heart_sensor.getBpm()));
        grid->addWidget(bpm, 2, 1, 1, 1);
    }
    
    void ViewerVisitor::visitSpeedometer(Core::Speedometer& speedometer) 
    {
        widget = new QWidget();

        QGridLayout* grid = new QGridLayout();
        widget->setLayout(grid);
        grid->setAlignment(Qt::AlignTop | Qt::AlignCenter);

        QLabel* training_time = new QLabel("Training time: " + QString::number(speedometer.getTrainingTime(), 'f', 2));
        grid->addWidget(training_time, 1, 1, 1, 1);

        QLabel* distance = new QLabel("Distance: " + QString::number(speedometer.getDistance()));
        grid->addWidget(distance, 2, 1, 1, 1);

        QLabel* speed = new QLabel("Avarage speed: " + QString::number(speedometer.getSpeed()));
        grid->addWidget(speed, 2, 2, 1, 1);
    }
};