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
        std::vector<float> distance_vector;
        std::vector<float> speed_vector;

        public:
        Speedometer(unsigned int id, std::string name, std::string description, unsigned int age, float height, float weight, 
        unsigned int training_type, float training_time = 0, float avarage_speed = 0, float distance = 0);
        virtual ~Speedometer();

        std::string getType() const override;
        float getAvarageSpeed() const;
        float getDistance() const;
        std::vector<float> getDistanceVector() const;
        std::vector<float> getSpeedVector() const;

        void setAvarageSpeed(float new_avarage_speed);
        void setDistance(float new_distance);
        void setStandardSpeed();

        void simulate() override;
        void reset() override;

        void accept(IVisitor& visitor) override;
        void accept(IConstVisitor& const_visitor) const override;
    };
};

#endif