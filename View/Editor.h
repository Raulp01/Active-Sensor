#ifndef EDITOR
#define EDITOR

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>

#include "../IVisitor.h"
#include "../Core/Activity.h"
#include "MainWindow.h"
#include "EditorVisitor.h"

namespace View {

    class Editor : public QWidget, public Core::IVisitor
    {
        Q_OBJECT

        private:
        MainWindow* mainwindow;
        Core::Sensor& sensor;
        QLineEdit* name;
        QTextEdit* description;
        QSpinBox* age;
        QDoubleSpinBox* height;
        QDoubleSpinBox* weight;
        QComboBox* training_type;
        QDoubleSpinBox* training_time;

        public:
        Editor(MainWindow* mainwindow, Core::Sensor& sensor, QWidget* parent = 0);

        QWidget* getWidget();

        virtual void visitCaloriesCounter(Core::CaloriesCounter& calories_counter);
        virtual void visitActivity(Core::Activity& activity);
        virtual void visitHeartSensor(Core::HeartSensor& heart_sensor);
        virtual void visitSpeedometer(Core::Speedometer& speedometer);
    };

};

#endif