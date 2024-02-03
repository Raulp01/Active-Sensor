#include "CaloriesCounter.h"

namespace Core
{
    const float CaloriesCounter::bpm_percentage = 0.25;

    CaloriesCounter::CaloriesCounter(unsigned int id, std::string name, std::string description, unsigned int age, float height, float weight, unsigned int training_type,
    float training_time, unsigned int bpm, unsigned int calories) : Sensor(id, name, description, age, height, weight, training_type, training_time),
    HeartSensor(id, name, description, age, height, weight, training_type, training_time, bpm), calories(calories)
    {
        setStandardCalories();
        calories_vector.push_back(getCalories());
    }
    
    CaloriesCounter::~CaloriesCounter() {}

    unsigned int CaloriesCounter::getCalories() const
    {
        return calories;
    }

    std::string CaloriesCounter::getType() const
    {
        return "CaloriesCounter";
    }

    std::vector<unsigned int> CaloriesCounter::getCaloriesVector() const
    {
        return calories_vector;
    }

    void CaloriesCounter::setCalories(unsigned int new_calories)
    {
        calories = new_calories;
    }

    void CaloriesCounter::setStandardCalories()
    {
        // Calcola calorie medie
        setCalories(getWeight() * getTrainingTime() + (getTrainingType()));
    }

    void CaloriesCounter::simulate() 
    {
        // Simulazione del sottooggetto
        HeartSensor::simulate();

        // Incidenza dei bpm nella simulazione del calcolo delle calorie bruciate (25%)
        float calories_range = getBpm() * bpm_percentage;
        /*
            Prende un numero casuale tra le calorie precedenti e le nuove calorie
            Questo per randomizzare l'aumento di calorie in delta-time
        */ 
        float rand_calories = getRandomNumber(getCalories(), getCalories() + calories_range);
        setCalories(rand_calories);
        calories_vector.push_back(getCalories());
    }

    // Reset del sottooggetto e pulizia dei dati di CaloriesCounter
    void CaloriesCounter::reset()
    {
        HeartSensor::reset();
        calories_vector.clear();
        setStandardCalories();
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