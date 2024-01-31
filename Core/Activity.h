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
        float training_time, unsigned int bpm = 0, float calories = 0, float avarage_speed = 0, float distance = 0);
        virtual ~Activity();

        std::string getType() const override;

        void simulate() override;
        void reset() override;

        void accept(IVisitor& visitor) override;
        void accept(IConstVisitor& const_visitor) const override;
    };
};

#endif