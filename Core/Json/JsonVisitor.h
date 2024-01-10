#ifndef JSON_VISITOR
#define JSON_VISITOR

#include <QJsonObject>
#include "../../IConstVisitor.h"
#include "../Activity.h"
#include "../CaloriesCounter.h"
#include "../HeartSensor.h"
#include "../Speedometer.h"

namespace Core {
namespace Json {

    class JsonVisitor: public IConstVisitor {
    private:
    QJsonObject object;

    public:
    QJsonObject getObject() const;
    void visitCaloriesCounter(const CaloriesCounter& calories_counter);
    void visitHeartSensor(const HeartSensor& heart_sensor);
    void visitSpeedometer(const Speedometer& speedometer);
    void visitActivity(const Activity& activity);
    };
}
}

#endif