#ifndef READER
#define READER

#include <map>
#include <QJsonObject>

#include "IReader.h"


namespace Core {
namespace Json {

class Reader: public IReader {
  private:
    std::map<unsigned int, Sensor*> cache;

  public:
    const std::map<unsigned int, Sensor*>& getCache() const;
    Reader& clear();
    virtual Sensor* read(const QJsonObject& object);

  private:
    Sensor* readHeartSensor(const QJsonObject& object) const;
    Sensor* readCaloriesCounter(const QJsonObject& object) const;
    Sensor* readSpeedometer(const QJsonObject& object) const;
    Sensor* readActivity(const QJsonObject& object) const;
};

}
}

#endif