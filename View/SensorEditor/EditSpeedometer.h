#ifndef EDIT_SPEEDOMETER
#define EDIT_SPEEDOMETER

#include "EditSensor.h"
#include "../../Core/Speedometer.h"
#include <QDoubleSpinBox>

namespace View {
namespace SensorEditor {

    class EditSpeedometer : public EditSensor
    {
        Q_OBJECT

        private:
        QDoubleSpinBox* distance;

        public:
        EditSpeedometer(QWidget* parent = 0);
        ~EditSpeedometer();
        virtual Core::Sensor* create(
            unsigned int id,
            QString& name,
            QString& description,
            unsigned int age,
            float height,
            float weight,
            unsigned int training_type,
            float training_time
        );

        void setValues(Core::Speedometer& speedometer);
    };
}
}

#endif