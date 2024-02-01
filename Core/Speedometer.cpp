#include "Speedometer.h"

namespace Core
{

    Speedometer::Speedometer(unsigned int id, std::string name, std::string description, unsigned int age, float height, float weight, 
    unsigned int training_type, float training_time, float avarage_speed, float distance) 
    : Sensor(id, name, description, age, height, weight, training_type, training_time), avarage_speed(avarage_speed), 
    distance(distance) 
    {
        setStandardSpeed();
    }
    
    Speedometer::~Speedometer() {};

    std::string Speedometer::getType() const
    {
        return "Speedometer";
    }

    float Speedometer::getAvarageSpeed() const
    {
        return avarage_speed;
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

    void Speedometer::setAvarageSpeed(float new_avarage_speed)
    {
        this->avarage_speed = new_avarage_speed;
    }

    void Speedometer::setDistance(float new_distance)
    {
        this->distance = new_distance;
    }

    void Speedometer::setStandardSpeed()
    {
        // Calcola la velocità la prima volta prendendo un numero casuale tra 1 e training_type + 2
        setAvarageSpeed(getRandomNumber(1, avarage_speed + getTrainingType() + 2));
        std::cout << "Speedometer: set to standard speed: " << getAvarageSpeed() << std::endl;
        speed_vector.push_back(getAvarageSpeed());
        std::cout << "Speedometer: speed vector: " << speed_vector.size() << std::endl;
        distance_vector.push_back(getDistance());
        std::cout << "Speedometer: distance vector: " << distance_vector.size() << std::endl;
    }

    void Speedometer::simulate() 
    {
        std::cout << "Speedometer::simulate()" << std::endl;
        Sensor::simulate();
        //Distanza calcolata ad ogni iterazione 
        setDistance(getAvarageSpeed() * getTrainingTime()); 
        std::cout << "Speedometer::simulate() distance: " << getDistance() << std::endl;
        distance_vector.push_back(getDistance());
        std::cout << "Speedometer::simulate() distance_vector: " << distance_vector.size() << std::endl;

        //Ricalcola la velocità con un numero semi-randomico
        float rand_speed = getRandomNumber(avarage_speed - getTrainingType(), avarage_speed + getTrainingType());
        setAvarageSpeed(rand_speed);
        std::cout << "Speedometer::simulate() avarage_speed: " << getAvarageSpeed() << std::endl;
        speed_vector.push_back(getAvarageSpeed());
        std::cout << "Speedometer::simulate() speed_vector: " << speed_vector.size() << std::endl;
    }

    void Speedometer::reset()
    {
        std::cout << "Speedometer::reset()" << std::endl;
        Sensor::reset();
        speed_vector.clear();
        std::cout << "Speedometer::reset() speed_vector: " << speed_vector.size() << std::endl;
        setAvarageSpeed(0);
        std::cout << "Speedometer::reset() avarage_speed: " << getAvarageSpeed() << std::endl;
        //speed_vector.push_back(getAvarageSpeed());
        distance_vector.clear();
        std::cout << "Speedometer::reset() distance_vector: " << distance_vector.size() << std::endl;
        setDistance(0);
        std::cout << "Speedometer::reset() distance: " << getDistance() << std::endl;
        distance_vector.push_back(getDistance());
        std::cout << "Speedometer::reset() distance_vector: " << distance_vector.size() << std::endl;
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