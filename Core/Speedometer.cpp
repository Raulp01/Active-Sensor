#include "Speedometer.h"

namespace Core
{
    Speedometer::Speedometer(unsigned int id, std::string name, std::string description, unsigned int age, float height, float weight, 
    unsigned int training_type, float training_time, float speed, float distance) 
    : Sensor(id, name, description, age, height, weight, training_type, training_time), speed(speed), 
    distance(distance) 
    {
        // Se il sensore viene caricato dal file, inserisce i dati nel vettore
        if(getSpeed() != 0 && getDistance() != 0)
        {
            // Resetta la distanza per iniziare una nuova simulazione
            setDistance(0);
            speed_vector.push_back(getSpeed());
            distance_vector.push_back(getDistance());
        }
        // Se il sensore viene creato per la prima volta o viene caricato dal file, ma ha fatto una prima iterazione
        // resetta i valori e richiama setStandardSpeed()
        else
        {
            setStandardSpeed();
        }
    }
    
    Speedometer::~Speedometer() {};

    std::string Speedometer::getType() const
    {
        return "Speedometer";
    }

    float Speedometer::getSpeed() const
    {
        return speed;
    }

    float Speedometer::getDistance() const
    {
        return distance;
    }

    std::vector<float> Speedometer::getDistanceVector() const
    {
        return distance_vector;
    }
    
    std::vector<float> Speedometer::getSpeedVector() const
    {
        return speed_vector;
    }

    void Speedometer::setSpeed(float new_avarage_speed)
    {
        speed = new_avarage_speed;
    }

    void Speedometer::setDistance(float new_distance)
    {
        distance = new_distance;
    }

    void Speedometer::setStandardSpeed()
    {
        setSpeed(0);
        setDistance(0);
        // Calcola la velocità la prima volta prendendo un numero casuale 
        setSpeed(trainingIntensity());
        speed_vector.push_back(getSpeed());
        setDistance(0);
        distance_vector.push_back(getDistance());
    }

    // Calcola la velocità randomicamente in base all'intensità dell'allenamento
    float Speedometer::trainingIntensity()
    {
        float speed_intensity = 0;
        switch (getTrainingType())
        {
        case 1:
            // Allenamento leggero: velocità tra 3 e 8
            speed_intensity = getRandomNumber(3, getTrainingType() + 7);
            break;
        case 2:
            // Allenamento medio: velocità tra 4 e 12
            speed_intensity = getRandomNumber(4, getTrainingType() + 10);
            break;
        case 3:
            // Allenamento intenso: velocità tra 13 e 23
            speed_intensity = getRandomNumber(13, getTrainingType() + 20);
            break;
        case 4:
            // Allenamento molto intenso: velocità tra 20 e 30
            speed_intensity = getRandomNumber(20, getTrainingType() + 26);
            break;
        case 5: 
            // Sforzo massimo: velocità tra i 30 e i 35
            speed_intensity = getRandomNumber(30, getTrainingType() + 35);  
            break; 
        default:
            return speed_intensity = 1;
        }
        return speed_intensity;
    }

    void Speedometer::simulate() 
    {
        Sensor::simulate();

        //Distanza calcolata ad ogni chiamata di simulate() come distanza percorsa nello scarto di tempo
        float delta_distance = getSpeed() * getDeltaTime();
        setDistance(getDistance() + delta_distance); 

        // Aggiunge la distanza calcolata al vettore dei dati distance
        distance_vector.push_back(getDistance());

        //Ricalcola la velocità con un numero semi-randomico basato sull'intensità dell'allenamento
        float rand_speed = trainingIntensity();

        // Aggiorna speed e inserisce il nuovo dato nel vettore
        setSpeed(rand_speed);
        speed_vector.push_back(getSpeed());
    }

    void Speedometer::reset()
    {
        // Reset degli attributi della classe base
        Sensor::reset();

        //Pulizia dei vettori
        speed_vector.clear();

        distance_vector.clear();

        // Ricrea i valori per la prima iterazione della simulazione
        setStandardSpeed();
    }

    void Speedometer::accept(IVisitor& visitor)
    {
        visitor.visitSpeedometer(*this);
    }
    void Speedometer::accept(IConstVisitor& const_visitor) const
    {
        const_visitor.visitSpeedometer(*this);
    }
};