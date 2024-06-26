#ifndef HEARTSENSOR
#define HEARTSENSOR

#include "Sensor.h"

namespace Core
{
    class HeartSensor : virtual public Sensor
    {
        private:
        unsigned int bpm;
        std::vector<unsigned int> bpm_vector;
        static const unsigned int heart_frequence_constant;
        static const float age_percentage_constant;
        static const unsigned int rest_bpm_low;
        static const unsigned int rest_bpm_high;

        public:
        HeartSensor(unsigned int id, std::string name, std::string description, unsigned int age, float height, float weight, unsigned int training_type,
        float training_time = 0, unsigned int bpm = 0);
        virtual ~HeartSensor();

        unsigned int getBpm() const;
        std::string getType() const override;
        std::vector<unsigned int> getBpmVector() const;

        void setBpm(unsigned int new_bpm);

        void simulate() override;
        void reset() override;

        void accept(IVisitor& visitor) override;
        void accept(IConstVisitor& const_visitor) const override;

        private:
        void setStandardBpm();
    };
};

#endif