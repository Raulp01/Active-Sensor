#include "Activity.h"

namespace Core
{
    Activity::Activity(unsigned int id, std::string name, std::string description, unsigned int age, float height, float weight, unsigned int training_type,
    float training_time, unsigned int bpm, float calories, float speed, float distance) :
    Sensor(id, name, description, age, height, weight, training_type, training_time), 
    CaloriesCounter(id, name, description, age, height, weight, training_type, training_time, bpm, calories),
    Speedometer(id, name, description, age, height, weight, training_type, training_time, speed, distance) {}

    Activity::~Activity() {}

    std::string Activity::getType() const
    {
        return "Activity";
    }

    void Activity::simulate() 
    {
        std::cout << "Activity::simulate()" << std::endl;
        CaloriesCounter::simulate();

        Speedometer::simulate();
    }

    void Activity::reset()
    {
        std::cout << "Activity::reset()" << std::endl;
        Speedometer::reset();
        CaloriesCounter::reset();
    }

    void Activity::accept(IVisitor& visitor)
    {
        visitor.visitActivity(*this);
    }

    void Activity::accept(IConstVisitor& const_visitor) const
    {
        const_visitor.visitActivity(*this);
    }
};