#ifndef INJECTOR
#define INJECTOR

#include "../../IVisitor.h"
#include "EditActivity.h"
#include "EditHeartSensor.h"
#include "EditCaloriesCounter.h"
#include "EditSpeedometer.h"

namespace View {
namespace SensorEditor {

    class SensorInjector : public Core::IVisitor
    {
        private:
        EditActivity& activity;
        EditCaloriesCounter& calories_counter;
        EditSpeedometer& speedometer;
        EditHeartSensor& heart_sensor;

        public:
        SensorInjector(
            EditActivity& activity,
            EditCaloriesCounter& calories_counter,
            EditSpeedometer& speedometer,
            EditHeartSensor& heart_sensor
        );

        virtual void visitHeartSensor(Core::HeartSensor& heart_sensor);
        virtual void visitCaloriesCounter(Core::CaloriesCounter& calories_counter);
        virtual void visitSpeedometer(Core::Speedometer& speedometer);
        virtual void visitActivity(Core::Activity& activity);
    };

    
}
}

#endif