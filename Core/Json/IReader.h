#ifndef IREADER
#define IREADER

#include <QJsonObject>

#include "../Sensor.h"

namespace Core {
namespace Json {

class IReader {
  public:
    virtual ~IReader() {};
    virtual Sensor* read(const QJsonObject& object) = 0;
};

}
}

#endif