#include "HeartSensor.h"

namespace Core
{
    // Costanti per il calcolo dei bpm
    const unsigned int HeartSensor::heart_frequence_constant = 208;
    const float HeartSensor::age_percentage_constant = 0.7;
    const unsigned int HeartSensor::rest_bpm_low = 60;
    const unsigned int HeartSensor::rest_bpm_high = 100;

    HeartSensor::HeartSensor(std::string description, unsigned int age, float height, float weight, TrainingType training_type,
        float training_time) : Sensor(description, age, height, weight, training_type, training_time) 
        {
            setId();
            setStandardBpm();
        }
    
    HeartSensor::~HeartSensor() {}

    unsigned int HeartSensor::getBpm() const
    {
        return bpm;
    }

    void HeartSensor::setId()
    {
        std::string str = "HeartSensor-" + std::to_string(Sensor::getCounter());
        Sensor::setId(str);
    }

    void HeartSensor::setBpm(unsigned int bpm_)
    {
        this->bpm = bpm_;
    }

    void HeartSensor::setStandardBpm()
    {
        // Calcola randomicamente i bpm minimi (per una persona adulta è tra 60 e 100)
        min_bpm = getRandomNumber(rest_bpm_low, rest_bpm_high);

        // Calcola i bpm medi in base ad una serie di fattori
        max_bpm = heart_frequence_constant - age_percentage_constant * getAge();

        // Crea i bpm medi moltiplicando i bpm massimi per l'intensità dell'allenamento
        unsigned int ran_bpm = (min_bpm + max_bpm) / 2 * getTrainingTime();

        bpm = getRandomNumber(min_bpm, ran_bpm);
    }

    void HeartSensor::simulate() 
    {
        setStandardBpm();
        unsigned int rand_bpm = getRandomNumber(getBpm() - 5, getBpm() + 5);
        setBpm(rand_bpm);
    }

    void HeartSensor::accept(IVisitor& visitor)
    {
        visitor.visitHeartSensor(*this);
    }

    void HeartSensor::accept(IConstVisitor& const_visitor)
    {
        const_visitor.visitHeartSensor(*this);
    }
};