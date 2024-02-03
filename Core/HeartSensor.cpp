#include "HeartSensor.h"

namespace Core
{
    // Costanti per il calcolo dei bpm
    const unsigned int HeartSensor::heart_frequence_constant = 208;
    const float HeartSensor::age_percentage_constant = 0.85;
    const unsigned int HeartSensor::rest_bpm_low = 60;
    const unsigned int HeartSensor::rest_bpm_high = 100;

    HeartSensor::HeartSensor(unsigned int id, std::string name, std::string description, unsigned int age, float height, float weight, unsigned int training_type,
    float training_time, unsigned int bpm) : Sensor(id, name, description, age, height, weight, training_type, training_time), bpm(bpm) 
    {
        if(bpm == 0)
        {
            setStandardBpm();
        }
        else
        {
            bpm_vector.push_back(bpm);
        }
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
        /*
            Calcola i bpm minimi sotto sforzo prendendo un numero casuale tra quelli
            di una persona a riposo (per una persona adulta è tra 60 e 100)    
        */
        unsigned int min_bpm = getRandomNumber(rest_bpm_low, rest_bpm_high);

        /* 
            Calcola i bpm massimi sotto sforzo in base all'età (più è alta l'età meno i bpm massimi)
            Si ottiene prendendo una costante teorica (208), togliendo l'età e calcolando l'85% di quel numero
        */
        unsigned int max_bpm = (heart_frequence_constant - getAge()) * age_percentage_constant;

        /* 
            Crea dei bpm medi e ci aggiunge un condizionamento dato dai bpm minimi per getTrainingType()/100
            Lo static_cast serve per calcolare un condizionamento più preciso per poi riconvertirlo
            min_bpm = 60 e gettrainingType()/100 = 0,05: 
            se unsigned int ho 60 * 0 = 0
            Se float ho 60 * 0.05 = 3
        */ 
        unsigned int ran_bpm = ((min_bpm + max_bpm) / 2) + (min_bpm * static_cast<float>(getTrainingType()) / 100);

        setBpm(getRandomNumber(ran_bpm, max_bpm));
        bpm_vector.push_back(getBpm());
    }

    void HeartSensor::simulate() 
    {
        Sensor::simulate();
        
        // Bpm nel tempo
        unsigned int rand_bpm = getRandomNumber(getBpm() - 5, getBpm() + 5);
        
        /*
            Se il valore casuale scende sotto la soglia minima a riposo, 
            porta il valore casuale un po' sopra il limite minimo
        */
        if(rand_bpm < 60)
        {
            rand_bpm = 63;
        }
        setBpm(rand_bpm);
        bpm_vector.push_back(getBpm());
    }

    void HeartSensor::reset()
    {
        Sensor::reset();
        bpm_vector.clear();
        setStandardBpm();
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