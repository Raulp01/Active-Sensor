#ifndef ACTIVITY
#define ACTIVITY

#include "../Core/HeartSensor.h"
#include "../Core/CaloriesCounter.h"
#include "../Core/Speedometer.h"

namespace Core
{
    class Activity : public CaloriesCounter, public Speedometer
    {
        public:
        Activity(std::string id, std::string description, unsigned int age, float height, float weight, TrainingType training_type,
        float training_time, float distance);

        void simulate() override;
    };
};

#endif