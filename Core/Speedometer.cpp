#include "Speedometer.h"

namespace Core
{
    Speedometer::Speedometer(unsigned int id, std::string name, std::string description, unsigned int age, float height, float weight, 
    unsigned int training_type, float training_time, float speed, float distance) 
    : Sensor(id, name, description, age, height, weight, training_type, training_time), speed(speed), 
    distance(distance) 
    {
        std::cout << "Speedometer::Speedometer()" << std::endl;
        // Se il sensore viene caricato dal file, inserisce i dati nel vettore
        if(getSpeed() != 0 && getDistance() != 0)
        {
            // Resetta la distanza per iniziare una nuova simulazione
            setDistance(0);
            std::cout << "Speedometer::Speedometer() costruttore: speed e distance != 0: " << getSpeed() << " " << getDistance() << std::endl;
            speed_vector.push_back(getSpeed());
            distance_vector.push_back(getDistance());
            std::cout << "Speedometer::Speedometer() speed_vector " << speed_vector.size() << std::endl;
            std::cout << "Speedometer::Speedometer() distance_vector " << distance_vector.size() << std::endl;
        }
        // Se il sensore viene creato per la prima volta o viene caricato dal file, ma ha fatto una prima iterazione
        // resetta i valori e richiama setStandardSpeed()
        else
        {
            std::cout << "Speedometer::Speedometer() costruttore: speed e distance  = 0" << std::endl;
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
        std::cout << "Speedometer::setStandardSpeed()";
        // Calcola la velocità la prima volta prendendo un numero casuale 
        std::cout << "Speedometer: set to standard speed: " << getSpeed() << std::endl;
        setSpeed(trainingIntensity());
        std::cout << "Speedometer: set to standard speed: " << getSpeed() << std::endl;
        speed_vector.push_back(getSpeed());
        std::cout << "Speedometer: speed vector: " << speed_vector.size() << std::endl;
        setDistance(0);
        distance_vector.push_back(getDistance());
        std::cout << "Speedometer: distance vector: " << distance_vector.size() << std::endl;
    }

    float Speedometer::trainingIntensity()
    {
        float speed_intensity = 0;
        // Calcola la velocità in base all'intensità dell'allenamento
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
        std::cout << "Speedometer::simulate()" << std::endl;
        Sensor::simulate();
        //Distanza calcolata ad ogni iterazione 

        // Distanza percorsa nell'aumento del tempo

        float delta_distance = getSpeed() * getDeltaTime();
        setDistance(getDistance() + delta_distance); 
        std::cout << "Speedometer::simulate() distance: " << getDistance() << std::endl;
        distance_vector.push_back(getDistance());
        std::cout << "Speedometer::simulate() distance_vector: " << distance_vector.size() << std::endl;

        //Ricalcola la velocità con un numero semi-randomico
        float rand_speed = trainingIntensity();

        setSpeed(rand_speed);
        std::cout << "Speedometer::simulate() avarage_speed: " << getSpeed() << std::endl;
        speed_vector.push_back(getSpeed());
        std::cout << "Speedometer::simulate() speed_vector: " << speed_vector.size() << std::endl;
    }

    void Speedometer::reset()
    {
        // Reset degli attributi della classe base
        std::cout << "Speedometer::reset()" << std::endl;
        Sensor::reset();

        //Pulizia dei vettori
        speed_vector.clear();
        std::cout << "Speedometer::reset() speed_vector: " << speed_vector.size() << std::endl;

        distance_vector.clear();
        std::cout << "Speedometer::reset() distance_vector: " << distance_vector.size() << std::endl;

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