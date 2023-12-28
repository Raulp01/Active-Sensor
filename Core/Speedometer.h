#ifndef SPEEDOMETER
#define SPEEDOMETER

#include "../Core/Sensor.h"

namespace Core
{
    class Speedometer : virtual public Sensor
    {
        private:
        float avarage_speed;
        float distance;
        static const unsigned int meters_in_km;
        static const unsigned int seconds_in_h; 

        public:
        Speedometer(std::string id, std::string description, unsigned int age, float height, float weight, TrainingType training_type,
        float training_time, float distance);

        float getAvarageSpeed() const;
        float getDistance() const;

        void setAvarageSpeed(float avarage_speed_);
        void setDistance(float distance_);
        void setStandardSpeed();

        void simulate() override;
    };
};

#endif