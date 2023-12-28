#ifndef SENSOR
#define SENSOR

#include <iostream>
#include <random>
#include "../IVisitor.h"
#include "../IConstVisitor.h"

namespace Core 
{
    enum TrainingType {light = 20, moderate = 40, high = 60, very_high = 80, maximum = 100};

    class Sensor
    {
        private:
        std::string id;
        std::string description;
        unsigned int age;
        float height;
        float weight;
        TrainingType training_type;
        float training_time;

        public:
        Sensor(std::string id, std::string description, unsigned int age, float height, float weight, TrainingType training_type,
        float training_time);

        // getter
        std::string getId() const;
        std::string getDescription() const;
        unsigned int getAge() const;
        float getHeight() const;
        float getWeight() const;
        float getTrainingType() const;
        float getTrainingTime() const;

        // setter
        void setDescription(std::string description_);
        void setAge(unsigned int age_);
        void setHeight(float height_);
        void setWeight(float weight_);
        void setTrainingType(TrainingType training_type_);
        void setTrainingTime(float training_time_);

        // Metodi per l'accesso del Visitor in lettura-scrittura e lettura
        virtual void accept(IVisitor& visitor) = 0;
        virtual void accept(IConstVisitor& const_visitor) = 0;

        // Metodo virtuale puro che permette la simulazione
        virtual void simulate() = 0;

        // Metodo che permette di calcolare un valore randomico in un range
        float getRandomNumber(float range_min, float range_max);
    };
}

#endif