#include "EditHeartSensor.h"
#include <QVBoxLayout>

namespace View {
namespace SensorEditor {
    EditHeartSensor::EditHeartSensor(QWidget* parent) : EditSensor(parent) 
    {
        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
        label = new QLabel("No additional parameters are required");
        layout->addWidget(label);
    }
    
    EditHeartSensor::~EditHeartSensor() {}

    Core::Sensor* EditHeartSensor::create(
        unsigned int id,
        QString& name,
        QString& description,
        unsigned int age,
        float height,
        float weight,
        unsigned int training_type,
        float training_time) 
    {
        return new Core::HeartSensor(
            id,
            name.toStdString(),
            description.toStdString(),
            age,
            height,
            weight,
            training_type,
            training_time
        );
    }
}
}