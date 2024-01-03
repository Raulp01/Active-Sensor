#ifndef HEARTSENSOR
#define HEARTSENSOR

#include "Sensor.h"

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
        HeartSensor(std::string description, unsigned int age, float height, float weight, TrainingType training_type,
        float training_time);
        virtual ~HeartSensor();

        unsigned int getBpm() const;
        void setId() override;
        void setBpm(unsigned int bpm_);
        void setStandardBpm();

        void simulate() override;

        void accept(IVisitor& visitor) override;
        void accept(IConstVisitor& const_visitor) override;
    };
};

#endif