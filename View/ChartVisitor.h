#ifndef CHARTVISITOR
#define CHARTVISITOR

#include <QWidget>
#include "../IConstVisitor.h"

namespace View
{
    class ChartVisitor : public QWidget, public Core::IConstVisitor
    {
        Q_OBJECT

        private:
        QWidget* widget;

        public:
        QWidget* getWidget();

        virtual void visitCaloriesCounter(const Core::CaloriesCounter& calories_counter);
        virtual void visitActivity(const Core::Activity& activity);
        virtual void visitHeartSensor(const Core::HeartSensor& heart_sensor);
        virtual void visitSpeedometer(const Core::Speedometer& speedometer);
    };
}

#endif