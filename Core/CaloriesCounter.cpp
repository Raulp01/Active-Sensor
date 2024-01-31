#include "CaloriesCounter.h"

namespace Core
{
    const float CaloriesCounter::bpm_percentage = 0.5;

    CaloriesCounter::CaloriesCounter(unsigned int id, std::string name, std::string description, unsigned int age, float height, float weight, unsigned int training_type,
    float training_time, unsigned int bpm, float calories) : Sensor(id, name, description, age, height, weight, training_type, training_time),
    HeartSensor(id, name, description, age, height, weight, training_type, training_time, bpm), calories(calories)
    {
        setStandardCalories();
    }
    
    CaloriesCounter::~CaloriesCounter() {}

    float CaloriesCounter::getCalories() const
    {
        return calories;
    }

    std::string CaloriesCounter::getType() const
    {
        return "CaloriesCounter";
    }

    void CaloriesCounter::setCalories(float new_calories)
    {
        this->calories = new_calories;
    }

    void CaloriesCounter::setStandardCalories()
    {
        // Calcola calorie medie
        setCalories(getWeight() * getTrainingTime() + (getTrainingType() * 2));
    }

    void CaloriesCounter::simulate() 
    {
        // Simulazione del sottooggetto
        HeartSensor::simulate();

        setStandardCalories();
        // Incidenza dei bpm nella simulazione del calcolo delle calorie bruciate (50%)
        float calories_range = getBpm() * bpm_percentage;
        float rand_calories = getRandomNumber(getCalories(), getCalories() + calories_range / 2);
        setCalories(rand_calories);
    }

    void CaloriesCounter::reset()
    {
        HeartSensor::reset();
        setCalories(0);
    }

    void CaloriesCounter::accept(IVisitor& visitor)
    {
        visitor.visitCaloriesCounter(*this);
    }
    
    void CaloriesCounter::accept(IConstVisitor& const_visitor) const
    {
        const_visitor.visitCaloriesCounter(*this);
    }
};