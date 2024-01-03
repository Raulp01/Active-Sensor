#include "Sensor.h"
#include "Error.h"

namespace Core
{
    unsigned int Sensor::id_count = 0;

    Sensor::Sensor(std::string description, unsigned int age, float height, float weight, TrainingType training_type,
        float training_time) : description(description), age(age), height(height), weight(weight), 
        training_type(training_type), training_time(training_time) 
        {
            // Limitatori per altezza, età, peso con gestione errori
            if(age > 110)
            {
                throw Error("Invalid age");
            }
            if(height < 0 || height > 2.5)
            {
                throw Error("Invali height");
            }
            if(training_time < 0)
            {
                throw Error("Training time cannot be negative");
            }
            if(weight < 0 || weight > 200)
            {
                throw Error("Invalid weight");
            }
            else
            {
                id_count++;
            }
        }

    Sensor::~Sensor() {}
    
    unsigned int Sensor::getCounter() const
    {
        return id_count;
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
        float tr = static_cast<float>(training_type) / 100;
        return tr;
    }

    float Sensor::getTrainingTime() const
    {
        return training_time;
    }

    void Sensor::setId(std::string id_)
    {
        this->id = id_;
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

    float Sensor::getRandomNumber(float range_min, float range_max)
    {
        // Provvede alla generazione di un numero randomico non-deterministico 
        std::random_device random;
        // Crea un numero pseudo casuale con il metodo Mersenne Twister
        std::mt19937 gen(random());
        // Crea una distribuzione nel range indicato
        std::uniform_real_distribution<> distr(range_min, range_max);
        // Ritorna il numero casuale nella distribuzione
        return distr(gen);
    }
};