#include "InfoVisitor.h"
#include <QVBoxLayout>

namespace View
{
    QWidget* InfoVisitor::getWidget()
    {
        return widget;
    }

    void InfoVisitor::visitCaloriesCounter(Core::CaloriesCounter& calories_counter)
    {
        widget = new QWidget();

        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);
        widget->setLayout(layout);

        QLabel* type = new QLabel("Type: " + QString::fromStdString(calories_counter.getType()));
        layout->addWidget(type);

        QLabel* bpm = new QLabel("BPM: " + QString::number(calories_counter.getBpm()));
        layout->addWidget(bpm);

        QLabel* calories = new QLabel("Calories: " + QString::number(calories_counter.getCalories()));
        layout->addWidget(calories);

        QPixmap image(":/Assets/CaloriesCounter.png");

        artwork = new QLabel();
        artwork->setPixmap(image.scaledToHeight(256));
        layout->addWidget(artwork);
    }

    void InfoVisitor::visitActivity(Core::Activity& activity)
    {
        widget = new QWidget();

        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);
        widget->setLayout(layout);

        QLabel* type = new QLabel("Type: " + QString::fromStdString(activity.getType()));
        layout->addWidget(type);

        QLabel* bpm = new QLabel("BPM: " + QString::number(activity.getBpm()));
        layout->addWidget(bpm);

        QLabel* calories = new QLabel("Calories: " + QString::number(activity.getCalories()));
        layout->addWidget(calories);

        QLabel* distance = new QLabel("Distance: " + QString::number(activity.getDistance()));
        layout->addWidget(distance);

        QLabel* speed = new QLabel("Speed: " + QString::number(activity.getSpeed()));
        layout->addWidget(speed);

        QPixmap image(":/Assets/Activity.png");

        artwork = new QLabel();
        artwork->setPixmap(image.scaledToHeight(256));
        layout->addWidget(artwork);
    }
    
    void InfoVisitor::visitHeartSensor(Core::HeartSensor& heart_sensor)
    {
        widget = new QWidget();

        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);
        widget->setLayout(layout);

        QLabel* type = new QLabel("Type: " + QString::fromStdString(heart_sensor.getType()));
        layout->addWidget(type);

        QLabel* bpm = new QLabel("BPM: " + QString::number(heart_sensor.getBpm()));
        layout->addWidget(bpm);

        QPixmap image(":/Assets/HeartSensor.png");

        artwork = new QLabel();
        artwork->setPixmap(image.scaledToHeight(256));
        layout->addWidget(artwork);
    }
    
    void InfoVisitor::visitSpeedometer(Core::Speedometer& speedometer)
    {
        widget = new QWidget();

        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);
        widget->setLayout(layout);

        QLabel* type = new QLabel("Type: " + QString::fromStdString(speedometer.getType()));
        layout->addWidget(type);

        QLabel* distance = new QLabel("Distance: " + QString::number(speedometer.getDistance()));
        layout->addWidget(distance);

        QLabel* speed = new QLabel("Speed: " + QString::number(speedometer.getSpeed()));
        layout->addWidget(speed);

        QPixmap image(":/Assets/Speedometer.png");

        artwork = new QLabel();
        artwork->setPixmap(image.scaledToHeight(256));
        layout->addWidget(artwork);
    }
}