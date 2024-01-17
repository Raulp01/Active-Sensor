#ifndef SENSOR
#define SENSOR

#include <iostream>
#include <random>
#include "../IVisitor.h"
#include "../IConstVisitor.h"

namespace Core 
{
    class Sensor
    {
        private:
        static unsigned int id_count;
        unsigned int id;
        std::string name;
        std::string description;
        unsigned int age;
        float height;
        float weight;
        unsigned int training_type;
        float training_time;

        public:
        Sensor(unsigned int id, std::string name, std::string description, unsigned int age, float height, float weight, unsigned int training_type,
        float training_time);
        virtual ~Sensor() = 0;

        // getter
        unsigned int getCounter() const;
        // Utile per ritornare la stringa col nome del tipo della classe per selezionare
        // l'artwork nell'interfaccia
        virtual std::string getType() const = 0;
        unsigned int getId() const;
        std::string getName() const;
        std::string getDescription() const;
        unsigned int getAge() const;
        float getHeight() const;
        float getWeight() const;
        unsigned int getTrainingType() const;
        std::string getTrainingTypeToString() const;
        float getTrainingTime() const;

        // setter
        void setId(unsigned int new_id);
        void setName(std::string new_name);
        void setDescription(std::string new_description_);
        void setAge(unsigned int new_age);
        void setHeight(float new_height);
        void setWeight(float new_weight);
        void setTrainingType(unsigned int new_training_type);
        void setTrainingTime(float new_training_time);

        // Overloading operatori
        bool operator==(const Sensor& sensor) const;

        // Metodi per l'accesso del Visitor in lettura-scrittura e lettura
        virtual void accept(IVisitor& visitor) = 0;
        virtual void accept(IConstVisitor& const_visitor) const = 0;

        // Metodo virtuale puro che permette la simulazione
        virtual void simulate() = 0;

        // Metodo che permette di calcolare un valore randomico in un range
        float getRandomNumber(float range_min, float range_max);
    };
};

#endif