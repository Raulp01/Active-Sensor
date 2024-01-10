#ifndef SPEEDOMETER
#define SPEEDOMETER

#include "Sensor.h"

namespace Core
{
    class Speedometer : virtual public Sensor
    {
        private:
        float avarage_speed;
        float distance;

        public:
        Speedometer(unsigned int id, std::string name, std::string description, unsigned int age, float height, float weight, unsigned int training_type,
        float training_time, float avarage_speed, float distance);
        virtual ~Speedometer();

        std::string getType() const override;
        float getAvarageSpeed() const;
        float getDistance() const;

        void setAvarageSpeed(float new_avarage_speed);
        void setDistance(float new_distance);
        void setStandardSpeed();

        void simulate() override;

        void accept(IVisitor& visitor) override;
        void accept(IConstVisitor& const_visitor) const override;
    };
};

#endif