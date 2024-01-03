#ifndef ACTIVITY
#define ACTIVITY

#include "HeartSensor.h"
#include "CaloriesCounter.h"
#include "Speedometer.h"

namespace Core
{
    class Activity : public CaloriesCounter, public Speedometer
    {
        public:
        Activity(std::string description, unsigned int age, float height, float weight, TrainingType training_type,
        float training_time, float distance);
        virtual ~Activity();

        void setId() override;
        void simulate() override;

        void accept(IVisitor& visitor) override;
        void accept(IConstVisitor& const_visitor) override;
    };
};

#endif