#include "../Core/CaloriesCounter.h"

namespace Core
{
    const float CaloriesCounter::bpm_percentage = 0.2;

    CaloriesCounter::CaloriesCounter(std::string id, std::string description, unsigned int age, float height, float weight, TrainingType training_type,
        float training_time) : HeartSensor(id, description, age, height, weight, training_type, training_time) 
        {
            setStandardCalories();
        }

    float CaloriesCounter::getCalories() const
    {
        return calories;
    }

    void CaloriesCounter::setCalories(float calories_)
    {
        this->calories = calories_;
    }

    void CaloriesCounter::setStandardCalories()
    {
        // Calcola calorie medie
        calories = getWeight() * getTrainingTime() * (getTrainingType() * 10);
    }

    void CaloriesCounter::simulate() 
    {
        // Simulazione del sottooggetto
        HeartSensor::simulate();

        setStandardCalories();
        // Incidenza dei bpm nella simulazione del calcolo delle calorie bruciate (20%)
        float calories_range = getBpm() * bpm_percentage;
        float rand_calories = getRandomNumber(getCalories() + calories_range, getCalories() - calories_range);
        setCalories(rand_calories);
    }
};