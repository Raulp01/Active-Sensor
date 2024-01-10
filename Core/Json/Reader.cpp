#include "Reader.h"

#include <stdexcept>
#include <QJsonArray>

#include "../Sensor.h"
#include "../HeartSensor.h"
#include "../CaloriesCounter.h"
#include "../Speedometer.h"
#include "../Activity.h"

namespace Core {
namespace Json {

const std::map<unsigned int, Sensor*>& Reader::getCache() const {
    return cache;
}

Reader& Reader::clear() {
    cache.clear();
    return *this;
}

Sensor* Reader::read(const QJsonObject& object) {
    QJsonValue type = object.value("type");
    if (type.isUndefined()) {
        std::invalid_argument("Missing sensor type");
    }
    const unsigned int identifier = object.value("id").toInt();
    if (cache.count(identifier) > 0) {
        return cache[identifier];
    }
    else if (type.toString().compare("Activity") == 0) {
        cache[identifier] = readActivity(object);
    }
    else if (type.toString().compare("Speedometer") == 0) {
        cache[identifier] = readSpeedometer(object);
    }
    else if (type.toString().compare("CaloriesCounter") == 0) {
        cache[identifier] = readCaloriesCounter(object);
    }
    else if (type.toString().compare("HeartSensor") == 0) {
        cache[identifier] = readHeartSensor(object);
    }
    else {
        throw std::invalid_argument("Unknown sensor");
    }
    return cache[identifier];
}

Sensor* Reader::readActivity(const QJsonObject& object) const {
    return new Activity(
        object.value("id").toInt(),
        object.value("name").toString().toStdString(),
        object.value("description").toString().toStdString(),
        object.value("age").toInt(),
        object.value("height").toDouble(),
        object.value("weight").toDouble(),
        object.value("training_type").toInt(),
        object.value("training_time").toDouble(),
        object.value("bpm").toInt(),
        object.value("calories").toDouble(),
        object.value("avarage_speed").toDouble(),
        object.value("distance").toDouble()
    );
}

Sensor* Reader::readHeartSensor(const QJsonObject& object) const {
    return new HeartSensor(
        object.value("id").toInt(),
        object.value("name").toString().toStdString(),
        object.value("description").toString().toStdString(),
        object.value("age").toInt(),
        object.value("height").toDouble(),
        object.value("weight").toDouble(),
        object.value("training_type").toInt(),
        object.value("training_time").toDouble(),
        object.value("bpm").toInt()
    );
}

Sensor* Reader::readCaloriesCounter(const QJsonObject& object) const {
    return new CaloriesCounter(
        object.value("id").toInt(),
        object.value("name").toString().toStdString(),
        object.value("description").toString().toStdString(),
        object.value("age").toInt(),
        object.value("height").toDouble(),
        object.value("weight").toDouble(),
        object.value("training_type").toInt(),
        object.value("training_time").toDouble(),
        object.value("bpm").toInt(),
        object.value("calories").toDouble()
    );
}

Sensor* Reader::readSpeedometer(const QJsonObject& object) const {
    return new Speedometer(
        object.value("id").toInt(),
        object.value("name").toString().toStdString(),
        object.value("description").toString().toStdString(),
        object.value("age").toInt(),
        object.value("height").toDouble(),
        object.value("weight").toDouble(),
        object.value("training_type").toInt(),
        object.value("training_time").toDouble(),
        object.value("avarage_speed").toDouble(),
        object.value("distance").toDouble()
    );
}

}
}