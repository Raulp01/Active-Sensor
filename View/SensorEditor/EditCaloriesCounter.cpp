#include "EditCaloriesCounter.h"

namespace View {
namespace SensorEditor {
    EditCaloriesCounter::EditCaloriesCounter(QWidget* parent) : EditSensor(parent) 
    {
        label = new QLabel("No additional parameters are required");
    }
    
    EditCaloriesCounter::~EditCaloriesCounter() {}

    Core::Sensor* EditCaloriesCounter::create(
        unsigned int id,
        QString& name,
        QString& description,
        unsigned int age,
        float height,
        float weight,
        unsigned int training_type,
        float training_time) 
    {
        return new Core::CaloriesCounter(
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