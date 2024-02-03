#ifndef VIEWER_VISITOR
#define VIEWER_VISITOR

#include "IConstVisitor.h"
#include "../Core/Activity.h"
#include "../Core/CaloriesCounter.h"
#include "../Core/HeartSensor.h"
#include "../Core/Speedometer.h"
#include <QWidget>
#include <QVBoxLayout>

namespace View
{
    class ViewerVisitor : public QWidget, public Core::IConstVisitor
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
};

#endif