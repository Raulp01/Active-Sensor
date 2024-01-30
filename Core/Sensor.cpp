#include "Sensor.h"

namespace Core
{
    unsigned int Sensor::id_count = 0;

    Sensor::Sensor(unsigned int id, std::string name, std::string description, unsigned int age, float height, float weight, unsigned int training_type,
    float training_time) : id(id), name(name), description(description), age(age), height(height), weight(weight), 
    training_type(training_type), training_time(training_time) {}

    Sensor::~Sensor() {}
    
    unsigned int Sensor::getCounter() const
    {
        return id_count;
    }

    std::string Sensor::getType() const {}

    unsigned int Sensor::getId() const
    {
        return id;
    }

    std::string Sensor::getName() const
    {
        return name;
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

    unsigned int Sensor::getTrainingType() const
    {
        return training_type;
    }

    std::string Sensor::getTrainingTypeToString() const
    {
        switch (training_type)
        {
        case 1:
            return "Light";
        case 2:
            return "Moderate";
        case 3:
            return "High";
        case 4:
            return "Very High";
        case 5:
            return "Maximum";
        default :
            return "Light";
        }
    }

    float Sensor::getTrainingTime() const
    {
        return training_time;
    }

    void Sensor::setId(unsigned int new_id)
    {
        this->id = new_id;
    }

    void Sensor::setName(std::string new_name)
    {
        this->name = new_name;
    }

    void Sensor::setDescription(std::string new_description)
    {
        this->description = new_description; 
    }

    void Sensor::setAge(unsigned int new_age)
    {
        this->age = new_age;
    }

    void Sensor::setHeight(float new_height)
    {
        this->height = new_height;
    }

    void Sensor::setWeight(float new_weight)
    {
        this->weight = new_weight;
    }

    void Sensor::setTrainingType(unsigned int new_trainig_type)
    {
        this->training_type = new_trainig_type;
    }

    void Sensor::setTrainingTime(float new_training_time)
    {
        this->training_time = new_training_time;
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