#ifndef ICONSTVISITOR
#define ICONSTVISITOR

namespace Core
{
    class HeartSensor;
    class CaloriesCounter;
    class Speedometer;
    class Activity;

    class IConstVisitor
    {
        public:
        ~IConstVisitor() = default;

        virtual void visitHeartSensor(const HeartSensor& heart_sensor) = 0;
        virtual void visitCaloriesCounter(const CaloriesCounter& calories_counter) = 0;
        virtual void visitSpeedometer(const Speedometer& speedometer) = 0;
        virtual void visitActivity(const Activity& activity) = 0;
    };
};

#endif