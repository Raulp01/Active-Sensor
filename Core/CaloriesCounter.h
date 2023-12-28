#ifndef CALORIESCOUNTER
#define CALORIESCOUNTER

#include "../Core/HeartSensor.h"

namespace Core
{
    class CaloriesCounter : public HeartSensor
    {
        private:
        float calories;
        static const float bpm_percentage;

        public:
        CaloriesCounter(std::string id, std::string description, unsigned int age, float height, float weight, TrainingType training_type,
        float training_time);

        float getCalories() const;
        void setCalories(float calories_);
        void setStandardCalories();

        void simulate() override;
    };
};

#endif