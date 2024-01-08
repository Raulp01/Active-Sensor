#ifndef EDITORVISITOR
#define EDITORVISITOR

#include "../IVisitor.h"
#include "../Core/Activity.h"
#include "../Core/CaloriesCounter.h"
#include "../Core/HeartSensor.h"
#include "../Core/Speedometer.h"
#include <QWidget>
#include <QPushButton>

namespace View
{
    class EditorVisitor : public QWidget, public Core::IVisitor
    {
        Q_OBJECT

        private:
        QWidget* widget;
        QPushButton* save;

        public:
        QWidget* getWidget();

        virtual void visitCaloriesCounter(Core::CaloriesCounter& calories_counter);
        virtual void visitActivity(Core::Activity& activity);
        virtual void visitHeartSensor(Core::HeartSensor& heart_sensor);
        virtual void visitSpeedometer(Core::Speedometer& speedometer);

        public slots:
    };
};

#endif