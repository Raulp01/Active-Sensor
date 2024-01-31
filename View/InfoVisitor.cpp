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

        QLabel* type = new QLabel("Type" + QString::fromStdString(calories_counter.getTrainingTypeToString()));
        layout->addWidget(type);

        layout->addStretch();

        QPixmap image("../Assets/CaloriesCounter.png");

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

        QLabel* type = new QLabel("Type" + QString::fromStdString(activity.getTrainingTypeToString()));
        layout->addWidget(type);

        layout->addStretch();

        QPixmap image("../Assets/Activity.png");

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

        QLabel* type = new QLabel("Type" + QString::fromStdString(heart_sensor.getTrainingTypeToString()));
        layout->addWidget(type);

        layout->addStretch();

        QPixmap image("../Assets/HeartSensor.png");

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

        QLabel* type = new QLabel("Type" + QString::fromStdString(speedometer.getTrainingTypeToString()));
        layout->addWidget(type);

        layout->addStretch();

        QPixmap image("../Assets/Speedometer.png");

        artwork = new QLabel();
        artwork->setPixmap(image.scaledToHeight(256));
        layout->addWidget(artwork);
    }
}