#ifndef EDITORVISITOR
#define EDITORVISITOR

#include "../IVisitor.h"
#include "../Core/Activity.h"
#include "../Core/CaloriesCounter.h"
#include "../Core/HeartSensor.h"
#include "../Core/Speedometer.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>

namespace View
{
    class EditorVisitor : public QWidget, public Core::IVisitor
    {
        Q_OBJECT

        private:
        QVBoxLayout* layout;
        QWidget* widget;
        QDoubleSpinBox* distance;
        QPushButton* apply;

        public:
        QWidget* getWidget();

        virtual void visitCaloriesCounter(Core::CaloriesCounter* calories_counter);
        virtual void visitActivity(Core::Activity* activity);
        virtual void visitHeartSensor(Core::HeartSensor* heart_sensor);
        virtual void visitSpeedometer(Core::Speedometer* speedometer);

        public slots:
        void editCaloriesCounter(Core::CaloriesCounter* calories_counter);
        void editHeartSensor(Core::HeartSensor* heart_sensor);
        void editSpeedometer(Core::Speedometer* speedometer);
        void editActivity(Core::Activity* activity);

        Core::CaloriesCounter& createCaloriesCounter();
        Core::HeartSensor& createHeartSensor();
        Core::Speedometer& createSpeedometer();
        Core::Activity& createActivity();
    };
};

#endif