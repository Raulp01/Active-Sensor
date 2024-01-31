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
        // Calcola velocità media in base alla distanza percorsa, il tempo di allenamento
        avarage_speed = getRandomNumber(1, avarage_speed + getTrainingType() + 2);
    }

    void Speedometer::simulate() 
    {
        Sensor::simulate();
        //Velocità nel tempo
        setDistance(getDistance() + getAvarageSpeed() * getTrainingTime()); 
        setAvarageSpeed(getDistance() / getTrainingTime());
        float rand_speed = getRandomNumber(avarage_speed - getTrainingType(), avarage_speed + getTrainingType());
        setAvarageSpeed(rand_speed);
    }

    void Speedometer::reset()
    {
        Sensor::reset();
        setDistance(0);
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