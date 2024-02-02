#include "Sensor.h"

namespace Core
{
    float Sensor::delta_time = 0.2;

    Sensor::Sensor(unsigned int id, std::string name, std::string description, unsigned int age, float height, float weight, 
    unsigned int training_type, float training_time) 
    : id(id), name(name), description(description), age(age), height(height), weight(weight), 
    training_type(training_type), training_time(training_time), time_changed(false) 
    {
        std::cout << "Sensor::Sensor()" << std::endl;
        time_vector.push_back(getTrainingTime());
        std::cout << "Sensor::Sensor() time_vector " << time_vector.size() << std::endl;
    }

    Sensor::~Sensor() {}

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

    bool Sensor::getTimeChanged() const
    {
        return time_changed;
    }

    std::vector<float> Sensor::getSensorVector() const
    {
        return time_vector;
    }

    float Sensor::getDeltaTime() const
    {
        return delta_time;
    }

    void Sensor::setId(unsigned int new_id)
    {
        id = new_id;
    }

    void Sensor::setName(std::string new_name)
    {
        name = new_name;
    }

    void Sensor::setDescription(std::string new_description)
    {
        description = new_description; 
    }

    void Sensor::setAge(unsigned int new_age)
    {
        age = new_age;
    }

    void Sensor::setHeight(float new_height)
    {
        height = new_height;
    }

    void Sensor::setWeight(float new_weight)
    {
        weight = new_weight;
    }

    void Sensor::setTrainingType(unsigned int new_trainig_type)
    {
        training_type = new_trainig_type;
    }

    void Sensor::setTrainingTime(float new_training_time)
    {
        training_time = new_training_time;
    }

    void Sensor::setTimeChanged(bool change)
    {
        time_changed = change;
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

    void Sensor::simulate()
    {
        std::cout << "Sensor::simulate()"<< std::endl;
        // Controllo per aumentare il tempo una volta nella gerarchia
        if(getTimeChanged() == false)
        {
            // Per semplicità il tempo è calcolato in centesimi: 1h = 1, 1/2h = 0.5
            std::cout << "Sensor::simulate() time_changed: " << getTimeChanged() << std::endl;
            setTrainingTime(getTrainingTime() + delta_time);
            std::cout << "Sensor::simulate() training_time: " << getTrainingTime() << std::endl;
            time_vector.push_back(getTrainingTime());
            std::cout << "Sensor::simulate() time_vector: " << time_vector.size() << std::endl;
            setTimeChanged(true);
            std::cout << "Sensor::simulate() time_changed: " << getTimeChanged() << std::endl;
        }
    }

    void Sensor::reset()
    {
        std::cout << "Sensor::reset()" << std::endl;
        setTimeChanged(false);
        std::cout << "Sensor::reset() time_changed: " << getTimeChanged() << std::endl;
        time_vector.clear();
        std::cout << "Sensor::reset() time_vector: " << time_vector.size() << std::endl;
        setTrainingTime(0);
        std::cout << "Sensor::reset() training_time: " << getTrainingTime() << std::endl;
        time_vector.push_back(getTrainingTime());
        std::cout << "Sensor::reset() time_vector: " << time_vector.size() << std::endl;
    }
};