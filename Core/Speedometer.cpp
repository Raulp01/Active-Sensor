#include "Speedometer.h"
#include "Error.h"

namespace Core
{

    Speedometer::Speedometer(std::string description, unsigned int age, float height, float weight, TrainingType training_type,
        float training_time, float distance) : Sensor(description, age, height, weight, training_type, training_time), 
        distance(distance) 
        {
            setId();
            setStandardSpeed();
            if(distance < 0)
            {
                throw Error("Invalid distance");
            }
        }
    Speedometer::~Speedometer() {};

    float Speedometer::getAvarageSpeed() const
    {
        return avarage_speed;
    }

    float Speedometer::getDistance() const
    {
        return distance;
    }

    void Speedometer::setId()
    {
        std::string str = "Speedometer-" + std::to_string(Sensor::getCounter());
        Sensor::setId(str);
    }

    void Speedometer::setAvarageSpeed(float avarage_speed_)
    {
        this->avarage_speed = avarage_speed_;
    }

    void Speedometer::setDistance(float distance_)
    {
        this->distance = distance_;
    }

    void Speedometer::setStandardSpeed()
    {
        // Calcola velocità media in base alla distanza percorsa, il tempo di allenamento
        avarage_speed = distance * getTrainingTime();
    }

    void Speedometer::simulate() 
    {
        float rand_speed = getRandomNumber(avarage_speed - getTrainingType() * 5, avarage_speed + getTrainingType() * 5);
        setAvarageSpeed(rand_speed);
    }

    void Speedometer::accept(IVisitor& visitor)
    {
        visitor.visitSpeedometer(*this);
    }
    void Speedometer::accept(IConstVisitor& const_visitor)
    {
        const_visitor.visitSpeedometer(*this);
    }
};