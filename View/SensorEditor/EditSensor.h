#ifndef EDIT_SENSOR
#define EDIT_SENSOR

#include <QWidget>
#include <QString>
#include "../../Core/Sensor.h"

namespace View {
namespace SensorEditor {

    class EditSensor : public QWidget
    {
        Q_OBJECT

        public:
        EditSensor(QWidget* parent = 0);
        virtual ~EditSensor();
        virtual Core::Sensor* create(
            unsigned int id,
            QString& name,
            QString& description,
            unsigned int age,
            float height,
            float weight,
            unsigned int training_type,
            float training_time
        ) = 0;
    };

}
}

#endif