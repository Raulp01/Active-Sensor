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
        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QLabel* type = new QLabel(QString::fromStdString(calories_counter.getTrainingTypeToString()));
        layout->addWidget(type);

        layout->addStretch();

        QPixmap image(":Assets/CaloriesCounter.png");

        artwork = new QLabel();
        artwork->setPixmap(image.scaledToHeight(256));
        layout->addWidget(artwork);

        widget = new QWidget();
        widget->setLayout(layout);
    }

    void InfoVisitor::visitActivity(Core::Activity& activity)
    {
        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QLabel* type = new QLabel(QString::fromStdString(activity.getTrainingTypeToString()));
        layout->addWidget(type);

        layout->addStretch();

        QPixmap image(":Assets/Activity.png");

        artwork = new QLabel();
        artwork->setPixmap(image.scaledToHeight(256));
        layout->addWidget(artwork);

        widget = new QWidget();
        widget->setLayout(layout);
    }
    
    void InfoVisitor::visitHeartSensor(Core::HeartSensor& heart_sensor)
    {
        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QLabel* type = new QLabel(QString::fromStdString(heart_sensor.getTrainingTypeToString()));
        layout->addWidget(type);

        layout->addStretch();

        QPixmap image(":Assets/HeartSensor.png");

        artwork = new QLabel();
        artwork->setPixmap(image.scaledToHeight(256));
        layout->addWidget(artwork);

        widget = new QWidget();
        widget->setLayout(layout);
    }
    
    void InfoVisitor::visitSpeedometer(Core::Speedometer& speedometer)
    {
        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QLabel* type = new QLabel(QString::fromStdString(speedometer.getTrainingTypeToString()));
        layout->addWidget(type);

        layout->addStretch();

        QPixmap image(":Assets/Speedometer.png");

        artwork = new QLabel();
        artwork->setPixmap(image.scaledToHeight(256));
        layout->addWidget(artwork);

        widget = new QWidget();
        widget->setLayout(layout);
    }
}