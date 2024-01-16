#ifndef EDIT_HEARTSENSOR
#define EDIT_HEARTSENSOR

#include "EditSensor.h"
#include "../../Core/HeartSensor.h"
#include <QLabel>

namespace View {
namespace SensorEditor {

    class EditHeartSensor : public EditSensor
    {
        Q_OBJECT

        private:
        QLabel* label;

        public:
        EditHeartSensor(QWidget* parent = 0);
        ~EditHeartSensor();
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
    };
}
}

#endif