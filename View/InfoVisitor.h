#ifndef INFO_VISITOR
#define INFO_VISITOR

#include <QWidget>
#include "../IVisitor.h"
#include <QLabel>
#include "Info.h"

namespace View
{
    class InfoVisitor : public QWidget, public Core::IVisitor
    {
        Q_OBJECT

        private:
        QWidget* widget;
        QLabel* artwork;

        public:
        QWidget* getWidget();

        virtual void visitCaloriesCounter(Core::CaloriesCounter& calories_counter);
        virtual void visitActivity(Core::Activity& activity);
        virtual void visitHeartSensor(Core::HeartSensor& heart_sensor);
        virtual void visitSpeedometer(Core::Speedometer& speedometer);
    };
}

#endif