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
        Activity(unsigned int id, std::string name, std::string description, unsigned int age, float height, float weight, unsigned int training_type,
        float training_time, unsigned int bpm, float calories, float avarage_speed, float distance);
        virtual ~Activity();

        std::string getType() const override;

        void simulate() override;

        void accept(IVisitor& visitor) override;
        void accept(IConstVisitor& const_visitor) const override;
    };
};

#endif