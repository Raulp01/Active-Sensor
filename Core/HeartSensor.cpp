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
        this->bpm = new_bpm;
    }

    void HeartSensor::setStandardBpm()
    {
        // Calcola randomicamente i bpm minimi (per una persona adulta è tra 60 e 100)
        min_bpm = getRandomNumber(rest_bpm_low, rest_bpm_high);

        // Calcola i bpm medi in base ad una serie di fattori
        max_bpm = heart_frequence_constant - age_percentage_constant * getAge();

        // Crea i bpm medi moltiplicando i bpm massimi per l'intensità dell'allenamento
        unsigned int ran_bpm = (min_bpm + max_bpm) / 2 * getTrainingType();

        setBpm(getRandomNumber(min_bpm, ran_bpm));
        bpm_vector.push_back(getBpm());
    }

    void HeartSensor::simulate() 
    {
        HeartSensor::simulate();
        // Bpm nel tempo

        unsigned int rand_bpm = getRandomNumber(getBpm() - 5, getBpm() + 5);
        setBpm(rand_bpm);
        bpm_vector.push_back(getBpm());
    }

    void HeartSensor::reset()
    {
        Sensor::reset();
        bpm_vector.clear();
        setBpm(0);
        bpm_vector.push_back(getBpm());
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