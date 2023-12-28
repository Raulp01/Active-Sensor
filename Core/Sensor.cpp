#include "../Core/Sensor.h"

namespace Core
{
    Sensor::Sensor(std::string id, std::string description, unsigned int age, float height, float weight, TrainingType training_type,
        float training_time) : id(id), description(description), age(age), height(height), weight(weight), 
        training_type(training_type), training_time(training_time) 
        {
            // Limitatori per altezza, età, peso con gestione errori
        }

    std::string Sensor::getId() const
    {
        return id;
    }

    std::string Sensor::getDescription() const
    {
        return description;
    }

    unsigned int Sensor::getAge() const
    {
        return age;
    }

    float Sensor::getHeight() const
    {
        return height;
    }

    float Sensor::getWeight() const
    {
        return weight;
    }

    float Sensor::getTrainingType() const
    {
        // Ritorna il valore in percentuale del tipo di allenamento
        float tr = training_type / 100;
        return tr;
    }

    float Sensor::getTrainingTime() const
    {
        return training_time;
    }

    void Sensor::setDescription(std::string description_)
    {
        this->description = description_; 
    }

    void Sensor::setAge(unsigned int age_)
    {
        this->age = age_;
    }

    void Sensor::setHeight(float height_)
    {
        this->height = height_;
    }

    void Sensor::setWeight(float weight_)
    {
        this->weight = weight_;
    }

    void Sensor::setTrainingType(TrainingType trainig_type_)
    {
        this->training_type = trainig_type_;
    }

    void Sensor::setTrainingTime(float training_time_)
    {
        this->training_time = training_time_;
    }

    void Sensor::simulate() {}

    float Sensor::getRandomNumber(float range_min, float range_max)
    {
        // Provvede alla generazione di un numero randomico non-deterministico 
        std::random_device random;
        // Crea un numero pseudo casuale con il metodo Mersenne Twister
        std::mt19937 gen(random());
        // Crea una distribuzione nel range indicato
        std::uniform_real_distribution<> distrib(range_min, range_max);
        // Ritorna il numero casuale nella distribuzione
        return distrib(gen);
    }
};