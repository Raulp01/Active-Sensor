#ifndef IVISITOR
#define IVISITOR

namespace Core
{
    class HeartSensor;
    class CaloriesCounter;
    class Speedometer;
    class Activity;

    class IVisitor
    {
        public:
        ~IVisitor() = default;

        virtual void visitHeartSensor(HeartSensor& heart_sensor) = 0;
        virtual void visitCaloriesCounter(CaloriesCounter& calories_counter) = 0;
        virtual void visitSpeedometer(Speedometer& speedometer) = 0;
        virtual void visitActivity(Activity& activity) = 0;
    };
};

#endif