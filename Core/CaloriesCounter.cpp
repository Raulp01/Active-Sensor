#include "CaloriesCounter.h"

namespace Core
{
    const float CaloriesCounter::bpm_percentage = 0.5;

    CaloriesCounter::CaloriesCounter(std::string description, unsigned int age, float height, float weight, TrainingType training_type,
        float training_time) : Sensor(description, age, height, weight, training_type, training_time),
        HeartSensor(description, age, height, weight, training_type, training_time) 
        {
            setId();
            setStandardCalories();
        }
    
    CaloriesCounter::~CaloriesCounter() {}

    float CaloriesCounter::getCalories() const
    {
        return calories;
    }

    void CaloriesCounter::setId()
    {
        std::string str = "CaloriesCounter-" + std::to_string(Sensor::getCounter());
        Sensor::setId(str);
    }

    void CaloriesCounter::setCalories(float calories_)
    {
        this->calories = calories_;
    }

    void CaloriesCounter::setStandardCalories()
    {
        // Calcola calorie medie
        calories = getWeight() * getTrainingTime() + (getTrainingType() * 10);
    }

    void CaloriesCounter::simulate() 
    {
        // Simulazione del sottooggetto
        HeartSensor::simulate();

        setStandardCalories();
        // Incidenza dei bpm nella simulazione del calcolo delle calorie bruciate (20%)
        float calories_range = getBpm() * bpm_percentage;
        float rand_calories = getRandomNumber(getCalories(), getCalories() + calories_range / 2);
        setCalories(rand_calories);
    }

    void CaloriesCounter::accept(IVisitor& visitor)
    {
        visitor.visitCaloriesCounter(*this);
    }
    
    void CaloriesCounter::accept(IConstVisitor& const_visitor)
    {
        const_visitor.visitCaloriesCounter(*this);
    }
};