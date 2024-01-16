#include "TypeSelector.h"

#include <QLabel>
#include <QGridLayout>

namespace View {
    
    TypeSelector::TypeSelector()
    {
        QGridLayout* layout = new QGridLayout();
        layout->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

        QLabel* label = new QLabel("Choose a type:");
        layout->addWidget(label, 0, 0);

        select_heartsensor = new QPushButton("Heart Sensor");
        layout->addWidget(select_heartsensor, 1, 0, 1, 1);
        connect(select_heartsensor, &QPushButton::pressed, this, &chooseHeartSensor);

        select_caloriescounter = new QPushButton("Calories Counter");
        layout->addWidget(select_caloriescounter, 1, 1, 1, 1);
        connect(select_caloriescounter, &QPushButton::pressed, this, &chooseCaloriesCounter);

        select_speedometer = new QPushButton("Speedometer");
        layout->addWidget(select_speedometer, 1, 2, 1, 1);
        connect(select_speedometer, &QPushButton::pressed, this, &chooseSpeedometer);

        select_activity = new QPushButton("Activity");
        layout->addWidget(select_activity, 1, 3, 1, 1);
        connect(select_activity, &QPushButton::pressed, this, &chooseActivity);
    }

    void TypeSelector::chooseHeartSensor()
    {
        EditorVisitor visitor;
        heart_sensor->accept(visitor);

        this->close();
    }
}