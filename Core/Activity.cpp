#include "../Core/Activity.h"

namespace Core
{
    Activity::Activity(std::string id, std::string description, unsigned int age, float height, float weight, TrainingType training_type,
        float training_time, float distance) :
        Sensor(id, description, age, height, weight, training_type, training_time), 
        CaloriesCounter(id, description, age, height, weight, training_type, training_time),
        Speedometer(id, description, age, height, weight, training_type, training_time, distance) {}

    void Activity::simulate() 
    {
        CaloriesCounter::simulate();

        Speedometer::simulate();
    }

    /* int main(void)
    {
    } */
};