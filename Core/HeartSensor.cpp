#include "../Core/HeartSensor.h"

namespace Core
{
    // Costanti per il calcolo dei bpm
    const unsigned int HeartSensor::heart_frequence_constant = 208;
    const float HeartSensor::age_percentage_constant = 0.7;
    const unsigned int HeartSensor::rest_bpm_low = 60;
    const unsigned int HeartSensor::rest_bpm_high = 100;

    HeartSensor::HeartSensor(std::string id, std::string description, unsigned int age, float height, float weight, TrainingType training_type,
        float training_time) : Sensor(id, description, age, height, weight, training_type, training_time) 
        {
            setStandardBpm();
        }

    unsigned int HeartSensor::getBpm() const
    {
        return bpm;
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
        unsigned int ran_bpm = min_bpm + max_bpm * getTrainingTime();

        bpm = getRandomNumber(ran_bpm - 10, ran_bpm + 10);
    }

    void HeartSensor::simulate() 
    {
        setStandardBpm();
        unsigned int rand_bpm = getRandomNumber(getBpm() - 5, getBpm() + 5);
        setBpm(rand_bpm);
    }
};