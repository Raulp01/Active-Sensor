#ifndef HEARTSENSOR
#define HEARTSENSOR

#include "../Core/Sensor.h"

namespace Core
{
    class HeartSensor : virtual public Sensor
    {
        private:
        unsigned int bpm;
        unsigned int max_bpm;
        unsigned int min_bpm;
        static const unsigned int heart_frequence_constant;
        static const float age_percentage_constant;
        static const unsigned int rest_bpm_low;
        static const unsigned int rest_bpm_high;

        public:
        HeartSensor(std::string id, std::string description, unsigned int age, float height, float weight, TrainingType training_type,
        float training_time);

        unsigned int getBpm() const;
        void setBpm(unsigned int bpm_);
        void setStandardBpm();

        void simulate() override;
    };
};

#endif