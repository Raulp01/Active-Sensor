#ifndef TYPESELECTOR
#define TYPESELECTOR

#include <QWidget>
#include "EditorVisitor.h"
#include <QPushButton>

namespace View {

    class TypeSelector : public QWidget
    {
        Q_OBJECT

        private:
        Core::HeartSensor* heart_sensor;
        QPushButton* select_heartsensor;
        QPushButton* select_caloriescounter;
        QPushButton* select_speedometer;
        QPushButton* select_activity;

        public:
        TypeSelector();

        public slots:
        void chooseHeartSensor();
        void chooseCaloriesCounter();
        void chooseSpeedometer();
        void chooseActivity();
    };
}

#endif