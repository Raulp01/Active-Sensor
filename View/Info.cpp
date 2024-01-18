#include "Info.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "InfoVisitor.h"

namespace View
{
    Info::Info(Core::Sensor& sensor, QWidget* parent) : sensor(sensor), QWidget(parent)
    {
        QHBoxLayout* h_layout = new QHBoxLayout();
        h_layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QVBoxLayout* icon_layout = new QVBoxLayout();
        icon_layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        InfoVisitor visitor;
        sensor.accept(visitor);
        icon_layout->addWidget(visitor.getWidget());

        QVBoxLayout* info_layout = new QVBoxLayout();
        info_layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        sensor_id = new QLabel();
        info_layout->addWidget(sensor_id);

        sensor_name = new QLabel();
        info_layout->addWidget(sensor_name);

        sensor_training_type = new QLabel();
        info_layout->addWidget(sensor_training_type);

        h_layout->addLayout(icon_layout);
        h_layout->addLayout(info_layout);

        this->show();
    }  

    void Info::show()
    {
        sensor_id->setText("Id: " + QString::number(sensor.getId()));
        sensor_name->setText("Name: " + QString::fromStdString(sensor.getName()));
        sensor_training_type->setText("Training intensity: " + QString::number(sensor.getTrainingType()));
    }
}