#include "Activity.h"

namespace Core
{
    Activity::Activity(std::string description, unsigned int age, float height, float weight, TrainingType training_type,
        float training_time, float distance) :
        Sensor(description, age, height, weight, training_type, training_time), 
        CaloriesCounter(description, age, height, weight, training_type, training_time),
        Speedometer(description, age, height, weight, training_type, training_time, distance) 
        {
            setId();
        }
    
    Activity::~Activity() {}

    void Activity::setId()
    {
        std::string str = "Activity-" + std::to_string(Sensor::getCounter());
        Sensor::setId(str);
    }

    void Activity::simulate() 
    {
        CaloriesCounter::simulate();

        Speedometer::simulate();
    }

    void Activity::accept(IVisitor& visitor)
    {
        visitor.visitActivity(*this);
    }

    void Activity::accept(IConstVisitor& const_visitor)
    {
        const_visitor.visitActivity(*this);
    }
};