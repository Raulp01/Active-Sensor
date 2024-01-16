#include "EditSpeedometer.h"
#include <QFormLayout>

namespace View {
namespace SensorEditor {
    EditSpeedometer::EditSpeedometer(QWidget* parent) : EditSensor(parent) 
    {
        QFormLayout* form = new QFormLayout(this);
        form->setLabelAlignment(Qt::AlignRight | Qt::AlignTop);

        distance = new QDoubleSpinBox();
        distance->setMinimum(0);
        form->addRow("Distance:", distance);
    }
    
    EditSpeedometer::~EditSpeedometer() {}

    Core::Sensor* EditSpeedometer::create(
        unsigned int id,
        QString& name,
        QString& description,
        unsigned int age,
        float height,
        float weight,
        unsigned int training_type,
        float training_time) 
    {
        return new Core::Speedometer(
            id,
            name.toStdString(),
            description.toStdString(),
            age,
            height,
            weight,
            training_type,
            training_time,
            distance->value()
        );
    }

    void EditSpeedometer::setValues(Core::Speedometer& speedometer)
    {
        distance->setValue(speedometer.getDistance());
    }
}
}