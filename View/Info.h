#ifndef INFO
#define INFO

#include "../Core/Activity.h"
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

namespace View
{
    class Info : public QWidget
    {
        Q_OBJECT

        private:
        const Core::Sensor& sensor;
        QLabel* sensor_id;
        QLabel* sensor_name;
        QLabel* sensor_training_type;

        public:
        Info(Core::Sensor& sensor, QWidget* parent = 0);
        void show();

        // Probabile bug: quando modifico il viewer dell'info, non penso venga aggiornata
        // Probabilmente sistemato quando Visitor per Scrollbar
    };
};

#endif