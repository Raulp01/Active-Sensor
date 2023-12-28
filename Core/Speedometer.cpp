#include "../Core/Speedometer.h"

namespace Core
{
    const unsigned int Speedometer::meters_in_km = 1000;
    const unsigned int Speedometer::seconds_in_h = 3600;

    Speedometer::Speedometer(std::string id, std::string description, unsigned int age, float height, float weight, TrainingType training_type,
        float training_time, float distance) : Sensor(id, description, age, height, weight, training_type, training_time), 
        distance(distance) 
        {

        }

    float Speedometer::getAvarageSpeed() const
    {
        return avarage_speed;
    }

    float Speedometer::getDistance() const
    {
        return distance;
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
        // Calcola velocità media in base alla distanza percorsa, il tempo di allenamento e l'intensità
        avarage_speed = (distance / meters_in_km) * (getTrainingTime() / seconds_in_h);
    }

    void Speedometer::simulate() 
    {
        float rand_speed = getRandomNumber(avarage_speed - 5, avarage_speed + 5);
        setAvarageSpeed(rand_speed);
    }
};