#include "InfoVisitor.h"
#include <QVBoxLayout>

namespace View
{
    QWidget* InfoVisitor::getWidget()
    {
        return widget;
    }

    // Informazioni specifiche sul sensore 

    void InfoVisitor::visitCaloriesCounter(const Core::CaloriesCounter& calories_counter)
    {
        widget = new QWidget();

        QVBoxLayout* layout = new QVBoxLayout();
        widget->setLayout(layout);

        QPixmap image(":/Assets/CaloriesCounter.png");

        artwork = new QLabel();
        artwork->setPixmap(image.scaledToHeight(125));
        artwork->setAlignment(Qt::AlignCenter);
        layout->addWidget(artwork);

        QLabel* type = new QLabel("Type: " + QString::fromStdString(calories_counter.getType()));
        layout->addWidget(type);

        QLabel* bpm = new QLabel("BPM: " + QString::number(calories_counter.getBpm()));
        layout->addWidget(bpm);

        QLabel* calories = new QLabel("Calories: " + QString::number(calories_counter.getCalories()));
        layout->addWidget(calories);
    }

    void InfoVisitor::visitActivity(const Core::Activity& activity)
    {
        widget = new QWidget();

        QVBoxLayout* layout = new QVBoxLayout();
        widget->setLayout(layout);

        QPixmap image(":/Assets/Activity.png");

        artwork = new QLabel();
        artwork->setPixmap(image.scaledToHeight(125));
        artwork->setAlignment(Qt::AlignCenter);
        layout->addWidget(artwork);

        QLabel* type = new QLabel("Type: " + QString::fromStdString(activity.getType()));
        layout->addWidget(type);

        QLabel* bpm = new QLabel("BPM: " + QString::number(activity.getBpm()));
        layout->addWidget(bpm);

        QLabel* calories = new QLabel("Calories: " + QString::number(activity.getCalories(), 'f', 2));
        layout->addWidget(calories);

        QLabel* distance = new QLabel("Distance: " + QString::number(activity.getDistance(), 'f', 2));
        layout->addWidget(distance);

        QLabel* speed = new QLabel("Speed: " + QString::number(activity.getSpeed(), 'f', 2));
        layout->addWidget(speed);
    }
    
    void InfoVisitor::visitHeartSensor(const Core::HeartSensor& heart_sensor)
    {
        widget = new QWidget();

        QVBoxLayout* layout = new QVBoxLayout();
        widget->setLayout(layout);

        QPixmap image(":/Assets/HeartSensor.png");

        artwork = new QLabel();
        artwork->setPixmap(image.scaledToHeight(125));
        artwork->setAlignment(Qt::AlignCenter);
        layout->addWidget(artwork);

        QLabel* type = new QLabel("Type: " + QString::fromStdString(heart_sensor.getType()));
        layout->addWidget(type);

        QLabel* bpm = new QLabel("BPM: " + QString::number(heart_sensor.getBpm()));
        layout->addWidget(bpm);
    }
    
    void InfoVisitor::visitSpeedometer(const Core::Speedometer& speedometer)
    {
        widget = new QWidget();

        QVBoxLayout* layout = new QVBoxLayout();
        widget->setLayout(layout);

        QPixmap image(":/Assets/Speedometer.png");

        artwork = new QLabel();
        artwork->setPixmap(image.scaledToHeight(125));
        artwork->setAlignment(Qt::AlignCenter);
        layout->addWidget(artwork);

        QLabel* type = new QLabel("Type: " + QString::fromStdString(speedometer.getType()));
        layout->addWidget(type);

        QLabel* distance = new QLabel("Distance: " + QString::number(speedometer.getDistance(), 'f', 2));
        layout->addWidget(distance);

        QLabel* speed = new QLabel("Speed: " + QString::number(speedometer.getSpeed(), 'f', 2));
        layout->addWidget(speed);
    }
}