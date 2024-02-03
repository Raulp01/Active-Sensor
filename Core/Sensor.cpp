#include "Sensor.h"

namespace Core
{
    float Sensor::delta_time = 0.2;

    Sensor::Sensor(unsigned int id, std::string name, std::string description, unsigned int age, float height, float weight, 
    unsigned int training_type, float training_time) 
    : id(id), name(name), description(description), age(age), height(height), weight(weight), 
    training_type(training_type), training_time(training_time), time_changed(false) 
    {
        // Inserisce i dati iniziali, raccolti dalla simulazione del sensore
        time_vector.push_back(getTrainingTime());
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

    /*
        Questa funzione serve da controllo per verificare che in una classe derivata
        di Sensor, non venga modificato il tempo alla costruzione dei sottooggetti.
        Senza questa funzione, all'invocazione di simulate() nella sottoclasse Activity,
        il tempo verrebbe modificato 3 volte (2 per CaloriesCounter (poiché chiama simulate()
        in HeartSensor), 1 in Speedometer).
        time_changed deve essere risettato a mano ad ogni invocazione di simulate o con reset() 
    */
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
        // Controllo per aumentare il tempo una volta nella gerarchia
        if(getTimeChanged() == false)
        {
            // Per semplicità il tempo è calcolato in centesimi: 1h = 1, 1/2h = 0.5
            setTrainingTime(getTrainingTime() + delta_time);

            time_vector.push_back(getTrainingTime());

            setTimeChanged(true);
        }
    }

    void Sensor::reset()
    {
        // Ripristina
        setTimeChanged(false);
        // Resetta il vettore dei dati training_time
        time_vector.clear();
        // Resetta il tempo
        setTrainingTime(0);
        time_vector.push_back(getTrainingTime());
    }
};