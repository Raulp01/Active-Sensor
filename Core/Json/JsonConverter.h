#ifndef JSON_CONVERTER
#define JSON_CONVERTER

#include <QJsonObject>
#include "../Sensor.h"
#include "IReader.h"

namespace Core {
namespace Json {

class JsonConverter 
{
  private:
    IReader& reader;

  public:
    JsonConverter(IReader& reader);
    const IReader& getReader() const;
    QJsonObject fromObject(const Sensor& item) const;
    Sensor* toObject(const QJsonObject& json) const;
};

}
}

#endif