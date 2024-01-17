#include "EditHeartSensor.h"

namespace View {
namespace SensorEditor {
    EditHeartSensor::EditHeartSensor(QWidget* parent) : EditSensor(parent) 
    {
        label = new QLabel("No additional parameters are required");
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