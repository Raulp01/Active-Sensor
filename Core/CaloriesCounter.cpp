#include "CaloriesCounter.h"

namespace Core
{
    const float CaloriesCounter::bpm_percentage = 0.25;

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
        std::cout << "CaloriesCounter::setStandardCalories()" << std::endl;
        // Calcola calorie medie
        setCalories(getWeight() * getTrainingTime() + (getTrainingType() * 2));
        std::cout << " calories set to " << getCalories() << " in setStandardCalories()" << std::endl;
    }

    void CaloriesCounter::simulate() 
    {
        std::cout << "CaloriesCounter::simulate()";
        // Simulazione del sottooggetto
        HeartSensor::simulate();

        setStandardCalories();
        // Incidenza dei bpm nella simulazione del calcolo delle calorie bruciate (25%)
        float calories_range = getBpm() * bpm_percentage;
        std::cout << "CaloriesCounter::simulate() calories_range set to " << calories_range << std::endl;
        float rand_calories = getRandomNumber(getCalories(), getCalories() + calories_range);
        setCalories(rand_calories);
        std::cout << "CaloriesCounter::simulate() calories " << getCalories() << std::endl;
        calories_vector.push_back(getCalories());
        std::cout << "CaloriesCounter::simulate() calories_vector " << calories_vector.size() << std::endl;
    }

    void CaloriesCounter::reset()
    {
        std::cout << "CaloriesCounter::reset()";
        HeartSensor::reset();
        calories_vector.clear();
        std::cout << "CaloriesCounter::reset() calories_vector " << calories_vector.size() << std::endl;
        setStandardCalories();
        std::cout << "CaloriesCounter::reset() calories " << getCalories() << std::endl;
        calories_vector.push_back(getCalories());
        std::cout << "CaloriesCounter::reset() calories_vector " << calories_vector.size() << std::endl;
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