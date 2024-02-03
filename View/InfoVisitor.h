#ifndef INFO_VISITOR
#define INFO_VISITOR

#include <QWidget>
#include "IConstVisitor.h"
#include <QLabel>
#include "Info.h"

namespace View
{
    class InfoVisitor : public QWidget, public Core::IConstVisitor
    {
        Q_OBJECT

        private:
        QWidget* widget;
        QLabel* artwork;

        public:
        QWidget* getWidget();

        virtual void visitCaloriesCounter(const Core::CaloriesCounter& calories_counter);
        virtual void visitActivity(const Core::Activity& activity);
        virtual void visitHeartSensor(const Core::HeartSensor& heart_sensor);
        virtual void visitSpeedometer(const Core::Speedometer& speedometer);
    };
}

#endif