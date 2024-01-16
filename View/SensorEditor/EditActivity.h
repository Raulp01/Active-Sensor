#ifndef EDIT_ACTIVITY
#define EDIT_ACTIVITY

#include "EditSensor.h"
#include "../../Core/Activity.h"
#include <QDoubleSpinBox>

namespace View {
namespace SensorEditor {

    class EditActivity : public EditSensor
    {
        Q_OBJECT

        private:
        QDoubleSpinBox* distance;

        public:
        EditActivity(QWidget* parent = 0);
        ~EditActivity();
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

        void setValues(Core::Activity& activity);
    };
}
}

#endif