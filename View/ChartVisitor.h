#ifndef CHARTVISITOR
#define CHARTVISITOR

#include <QWidget>
#include "../IConstVisitor.h"
#include "../Core/Activity.h"
#include <QVBoxLayout>

namespace View
{
    class ChartVisitor : public QWidget, public Core::IConstVisitor
    {
        Q_OBJECT

        private:
        QWidget* widget;
        QVBoxLayout* layout;

        public:
        QWidget* getWidget();
        virtual void visitCaloriesCounter(const Core::CaloriesCounter& calories_counter);
        virtual void visitActivity(const Core::Activity& activity);
        virtual void visitHeartSensor(const Core::HeartSensor& heart_sensor);
        virtual void visitSpeedometer(const Core::Speedometer& speedometer);

        public:
        QWidget* createBpmChart(const Core::HeartSensor& heart_sensor);
        QWidget* createCaloriesChart(const Core::CaloriesCounter& calories_counter);
        QWidget* createSpeedChart(const Core::Speedometer& speedometer);
    };
}

#endif