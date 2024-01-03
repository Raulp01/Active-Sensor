#ifndef CALORIESCOUNTER
#define CALORIESCOUNTER

#include "HeartSensor.h"

namespace Core
{
    class CaloriesCounter : public HeartSensor
    {
        private:
        float calories;
        static const float bpm_percentage;

        public:
        CaloriesCounter(std::string description, unsigned int age, float height, float weight, TrainingType training_type,
        float training_time);
        virtual ~CaloriesCounter();

        float getCalories() const;
        void setId() override;
        void setCalories(float calories_);
        void setStandardCalories();

        void simulate() override;

        void accept(IVisitor& visitor) override;
        void accept(IConstVisitor& const_visitor) override;
    };
};

#endif