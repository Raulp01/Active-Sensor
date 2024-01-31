#ifndef INFO
#define INFO

#include "../Core/Activity.h"
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>

namespace View
{
    class Info : public QWidget
    {
        Q_OBJECT

        private:
        Core::Sensor& sensor;
        QLabel* sensor_id;
        QLabel* sensor_name;
        QLabel* sensor_training_type;
        QPushButton* open;
        QPushButton* edit;
        QPushButton* remove;

        public:
        Info(Core::Sensor& sensor, QWidget* parent = 0);
        Core::Sensor& getSensor();

        signals:
        void showSensor(Core::Sensor& sensor);
        void editSensor(Core::Sensor& sensor);
        void deleteSensor(Core::Sensor& sensor);

        public slots:
        void emitShowSensor();
        void emitEditSensor();
        void emitDeleteSensor();
    };
};

#endif