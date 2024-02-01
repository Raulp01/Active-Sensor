#include "CaloriesCounter.h"

namespace Core
{
    const float CaloriesCounter::bpm_percentage = 0.5;

    CaloriesCounter::CaloriesCounter(unsigned int id, std::string name, std::string description, unsigned int age, float height, float weight, unsigned int training_type,
    float training_time, unsigned int bpm, float calories) : Sensor(id, name, description, age, height, weight, training_type, training_time),
    HeartSensor(id, name, description, age, height, weight, training_type, training_time, bpm), calories(calories)
    {
        setStandardCalories();
        calories_vector.push_back(getCalories());
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

    std::vector<float> CaloriesCounter::getCaloriesVector() const
    {
        return calories_vector;
    }

    void CaloriesCounter::setCalories(float new_calories)
    {
        calories = new_calories;
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
        calories_vector.push_back(getCalories());
    }

    void CaloriesCounter::reset()
    {
        HeartSensor::reset();
        calories_vector.clear();
        setCalories(0);
        calories_vector.push_back(getCalories());
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