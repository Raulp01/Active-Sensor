#ifndef VIEWERVISITOR
#define VIEWERVISITOR

#include "../IVisitor.h"
#include "../Core/Activity.h"
#include "../Core/CaloriesCounter.h"
#include "../Core/HeartSensor.h"
#include "../Core/Speedometer.h"
#include <QWidget>
#include <QVBoxLayout>

namespace View
{
    class ViewerVisitor : public QWidget, public Core::IVisitor
    {
        Q_OBJECT

        private:
        QWidget* widget;

        public:
        QWidget* getWidget();

        virtual void visitCaloriesCounter(Core::CaloriesCounter& calories_counter);
        virtual void visitActivity(Core::Activity& activity);
        virtual void visitHeartSensor(Core::HeartSensor& heart_sensor);
        virtual void visitSpeedometer(Core::Speedometer& speedometer);
    };
};

#endif