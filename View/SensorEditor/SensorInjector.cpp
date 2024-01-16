#include "SensorInjector.h"

namespace View {
namespace SensorEditor {

    SensorInjector::SensorInjector(EditActivity& activity, EditCaloriesCounter& calories_counter, 
        EditSpeedometer& speedometer, EditHeartSensor& heart_sensor) :
        activity(activity), calories_counter(calories_counter), speedometer(speedometer), heart_sensor(heart_sensor)
    {}

    void SensorInjector::visitActivity(Core::Activity& ac)
    {
        activity.setValues(ac);
    } 

    void SensorInjector::visitSpeedometer(Core::Speedometer& sp)
    {
        speedometer.setValues(sp);
    }

    void SensorInjector::visitHeartSensor(Core::HeartSensor& hs) {}
    void SensorInjector::visitCaloriesCounter(Core::CaloriesCounter& cc) {}

}
}