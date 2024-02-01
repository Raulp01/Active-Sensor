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
        speed_vector.push_back(getAvarageSpeed());
    }

    void Speedometer::simulate() 
    {
        Sensor::simulate();
        //Distanza calcolata ad ogni iterazione 
        setDistance(getAvarageSpeed() * getTrainingTime()); 
        distance_vector.push_back(getDistance());

        //Ricalcola la velocità con un numero semi-randomico
        float rand_speed = getRandomNumber(avarage_speed - getTrainingType(), avarage_speed + getTrainingType());
        setAvarageSpeed(rand_speed);
        speed_vector.push_back(getAvarageSpeed());
    }

    void Speedometer::reset()
    {
        setTimeChanged(false);
        Sensor::reset();
        speed_vector.clear();
        distance_vector.clear();
        setDistance(0);
        distance_vector.push_back(getDistance());
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