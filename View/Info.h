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
        const Core::Sensor& sensor;
        QLabel* sensor_id;
        QLabel* sensor_name;
        QLabel* sensor_training_type;
        QPushButton* open;
        QPushButton* edit;
        QPushButton* remove;

        public:
        Info(Core::Sensor& sensor, QWidget* parent = 0);
        void show();
        QPushButton* getOpenButton();
        QPushButton* getEditButton();
        QPushButton* getRemoveButton();

        // Probabile bug: quando modifico il viewer dell'info, non penso venga aggiornata
        // Probabilmente sistemato quando Visitor per Scrollbar
    };
};

#endif