#include "EditorVisitor.h"
#include <QVBoxLayout>

namespace View
{
    QWidget* EditorVisitor::getWidget()
    {
        return widget;
    }

    void EditorVisitor::visitHeartSensor(Core::HeartSensor& heart_sensor) 
    {
        save = new QPushButton("Save");
        connect(save, &QPushButton::pressed, this, &close);
    }

    void EditorVisitor::visitCaloriesCounter(Core::CaloriesCounter& calories) 
    {
        widget = new QWidget();
        


        save = new QPushButton("Save");
        connect(save, &QPushButton::pressed, this, &close);
    }
    
    void EditorVisitor::visitSpeedometer(Core::Speedometer& speedometer)
    {
        widget = new QWidget();

        save = new QPushButton("Save");
        // connect(save, &QPushButton::pressed, this, &close);
    }
};