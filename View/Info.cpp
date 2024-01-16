#include "Info.h"
#include <QVBoxLayout>

namespace View
{
    Info::Info(Core::Sensor& sensor, QWidget* parent) : sensor(sensor), QWidget(parent)
    {
        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        sensor_id = new QLabel();
        layout->addWidget(sensor_id);

        sensor_training_type = new QLabel();
        layout->addWidget(sensor_training_type);

        sensor_time = new QLabel();
        layout->addWidget(sensor_time);

        this->show();
    }  

    void Info::show()
    {
        sensor_id->setText("Id: " + QString::number(sensor.getId()));
        sensor_training_type->setText("Training intensity: " + QString::number(sensor.getTrainingType()));
        sensor_time->setText("Training time: " + QString::number(sensor.getTrainingTime()));
    }
}