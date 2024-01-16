#ifndef EDIT_CALORIESCOUNTER
#define EDIT_CALORIESCOUNTER

#include "EditSensor.h"
#include "../../Core/CaloriesCounter.h"
#include <QLabel>

namespace View {
namespace SensorEditor {

    class EditCaloriesCounter : public EditSensor
    {
        Q_OBJECT

        private:
        QLabel* label;

        public:
        EditCaloriesCounter(QWidget* parent = 0);
        ~EditCaloriesCounter();
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