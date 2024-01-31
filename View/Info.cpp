#include "Info.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "InfoVisitor.h"

namespace View
{
    Info::Info(Core::Sensor& sensor, QWidget* parent) : sensor(sensor), QWidget(parent)
    {
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

        QHBoxLayout* h_layout = new QHBoxLayout();
        h_layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QVBoxLayout* icon_layout = new QVBoxLayout();
        icon_layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        InfoVisitor visitor;
        sensor.accept(visitor);
        icon_layout->addWidget(visitor.getWidget());

        QVBoxLayout* info_layout = new QVBoxLayout();
        info_layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        sensor_id = new QLabel("Id: " + QString::number(sensor.getId()));
        info_layout->addWidget(sensor_id);

        sensor_name = new QLabel("Name: " + QString::fromStdString(sensor.getName()));
        info_layout->addWidget(sensor_name);

        sensor_training_type = new QLabel("Training intensity: " + QString::number(sensor.getTrainingType()));
        info_layout->addWidget(sensor_training_type);

        h_layout->addLayout(icon_layout);
        h_layout->addLayout(info_layout);
        layout->addLayout(h_layout);

        QHBoxLayout* button_layout = new QHBoxLayout();
        button_layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);
        layout->addLayout(button_layout);

        open = new QPushButton("Open");
        button_layout->addWidget(open);

        edit = new QPushButton("Edit");
        button_layout->addWidget(edit);

        remove = new QPushButton("Delete");
        button_layout->addWidget(remove);

        connect(open, &QPushButton::pressed, this, &Info::emitShowSensor);
        connect(edit, &QPushButton::pressed, this, &Info::emitEditSensor);
        connect(remove, &QPushButton::pressed, this, &Info::emitDeleteSensor);
    }  

    Core::Sensor& Info::getSensor()
    {
        return sensor;
    }

    void Info::emitShowSensor()
    {
        emit showSensor(sensor);
    }

    void Info::emitEditSensor()
    {
        emit editSensor(sensor);
    }

    void Info::emitDeleteSensor()
    {
        emit deleteSensor(sensor);
    }
}