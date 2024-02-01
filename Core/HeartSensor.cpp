#include "HeartSensor.h"

namespace Core
{
    // Costanti per il calcolo dei bpm
    const unsigned int HeartSensor::heart_frequence_constant = 208;
    const float HeartSensor::age_percentage_constant = 0.7;
    const unsigned int HeartSensor::rest_bpm_low = 60;
    const unsigned int HeartSensor::rest_bpm_high = 100;

    HeartSensor::HeartSensor(unsigned int id, std::string name, std::string description, unsigned int age, float height, float weight, unsigned int training_type,
        float training_time, unsigned int bpm) : Sensor(id, name, description, age, height, weight, training_type, training_time), bpm(bpm) 
        {
            setStandardBpm();
        }
    
    HeartSensor::~HeartSensor() {}

    unsigned int HeartSensor::getBpm() const
    {
        return bpm;
    }

    std::string HeartSensor::getType() const
    {
        return "HeartSensor";
    }

    std::vector<unsigned int> HeartSensor::getBpmVector() const
    {
        return bpm_vector;
    }

    void HeartSensor::setBpm(unsigned int new_bpm)
    {
        bpm = new_bpm;
    }

    void HeartSensor::setStandardBpm()
    {
        // Calcola randomicamente i bpm minimi (per una persona adulta è tra 60 e 100)
        min_bpm = getRandomNumber(rest_bpm_low, rest_bpm_high);
        std::cout << "Min bpm: " << min_bpm << std::endl;

        // Calcola i bpm medi in base ad una serie di fattori
        max_bpm = heart_frequence_constant - age_percentage_constant * getAge();
        std::cout << "Max bpm: " << max_bpm << std::endl;

        // Crea i bpm medi moltiplicando i bpm massimi per l'intensità dell'allenamento
        unsigned int ran_bpm = (min_bpm + max_bpm) / 2 * (static_cast<float>(getTrainingType()) / 10);
        std::cout << "Ran bpm: " << ran_bpm << std::endl;

        setBpm(getRandomNumber(min_bpm, ran_bpm));
        std::cout << "Bpm: " << getBpm() << std::endl;
        bpm_vector.push_back(getBpm());
        std::cout << "Bpm vector: " << bpm_vector.size() << std::endl;
    }

    void HeartSensor::simulate() 
    {
        std::cout << "HeartSensor::simulate()" << std::endl;
        Sensor::simulate();
        // Bpm nel tempo

        unsigned int rand_bpm = getRandomNumber(getBpm() - 5, getBpm() + 5);
        setBpm(rand_bpm);
        std::cout << "HeartSensor::simulate() bpm: " << getBpm() << std::endl;
        bpm_vector.push_back(getBpm());
        std::cout << "HeartSensor::simulate() bpm_vector: " << bpm_vector.size() << std::endl;
    }

    void HeartSensor::reset()
    {
        std::cout << "HeartSensor::reset()" << std::endl;
        Sensor::reset();
        bpm_vector.clear();
        std::cout << "HeartSensor::reset() bpm_vector: " << bpm_vector.size() << std::endl;
        setStandardBpm();
        std::cout << "HeartSensor::reset() bpm: " << getBpm() << std::endl;
    }

    void HeartSensor::accept(IVisitor& visitor)
    {
        visitor.visitHeartSensor(*this);
    }

    void HeartSensor::accept(IConstVisitor& const_visitor) const
    {
        const_visitor.visitHeartSensor(*this);
    }
};