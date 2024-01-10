#include "JsonVisitor.h"
#include "JsonConverter.h"

namespace Core {
namespace Json {

    JsonConverter::JsonConverter(IReader& reader) : reader(reader) {}

    const IReader& JsonConverter::getReader() const {
        return reader;
    }

    QJsonObject JsonConverter::fromObject(const Sensor& sensor) const {
        JsonVisitor visitor;
        sensor.accept(visitor);
        return visitor.getObject();
    }

    Sensor* JsonConverter::toObject(const QJsonObject& json) const {
        return reader.read(json);
    }

}
}