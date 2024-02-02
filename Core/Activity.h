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
        Activity(unsigned int id, std::string name, std::string description, unsigned int age = 1, float height = 0.6, float weight = 5, unsigned int training_type = 1,
        float training_time = 0, unsigned int bpm = 0, float calories = 0, float speed = 0, float distance = 0);
        virtual ~Activity();

        std::string getType() const override;

        void simulate() override;
        void reset() override;

        void accept(IVisitor& visitor) override;
        void accept(IConstVisitor& const_visitor) const override;
    };
};

#endif