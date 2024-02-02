#ifndef CALORIESCOUNTER
#define CALORIESCOUNTER

#include "HeartSensor.h"

namespace Core
{
    class CaloriesCounter : public HeartSensor
    {
        private:
        float calories;
        std::vector<float> calories_vector;
        static const float bpm_percentage;

        public:
        CaloriesCounter(unsigned int id, std::string name, std::string description, unsigned int age = 1, float height = 0.6, float weight = 5, unsigned int training_type = 1,
        float training_time = 0, unsigned int bpm = 0, float calories = 0);
        virtual ~CaloriesCounter();

        float getCalories() const;
        std::string getType() const override;
        std::vector<float> getCaloriesVector() const;

        void setCalories(float new_calories);
        void setStandardCalories();

        void simulate() override;
        void reset() override;

        void accept(IVisitor& visitor) override;
        void accept(IConstVisitor& const_visitor) const override;
    };
};

#endif