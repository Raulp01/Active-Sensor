#include "Sensor.h"
#include "Error.h"

namespace Core
{
    unsigned int Sensor::id_count = 0;

    Sensor::Sensor(std::string name, std::string description, unsigned int age, float height, float weight, TrainingType training_type,
        float training_time) : name(name), description(description), age(age), height(height), weight(weight), 
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

    std::string Sensor::getType() const
    {
        return "";
    }

    std::string Sensor::getId() const
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

    float Sensor::getTrainingType() const
    {
        // Ritorna il valore in percentuale del tipo di allenamento
        float tr = static_cast<float>(training_type) / 100;
        return tr;
    }

    std::string Sensor::getTrainingTypeToString() const
    {
        switch (training_type)
        {
        case TrainingType::light:
            return "Light";
        case TrainingType::moderate:
            return "Moderate";
        case TrainingType::high:
            return "High";
        case TrainingType::very_high:
            return "Very High";
        case TrainingType::maximum:
            return "Maximum";
        }
    }

    float Sensor::getTrainingTime() const
    {
        return training_time;
    }

    void Sensor::setId(std::string new_id)
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

    void Sensor::setTrainingType(TrainingType new_trainig_type)
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