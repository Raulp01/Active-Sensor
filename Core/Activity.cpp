#include "Activity.h"

namespace Core
{
    Activity::Activity(std::string name, std::string description, unsigned int age, float height, float weight, TrainingType training_type,
        float training_time, float distance) :
        Sensor(name, description, age, height, weight, training_type, training_time), 
        CaloriesCounter(name, description, age, height, weight, training_type, training_time),
        Speedometer(name, description, age, height, weight, training_type, training_time, distance) 
        {
            setId();
        }
    
    Activity::~Activity() {}

    std::string Activity::getId() const
    {
        return Sensor::getId();
    }

    std::string Activity::getType() const
    {
        return "Activity";
    }

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