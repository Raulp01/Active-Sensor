#include "JsonFile.h"
#include <iostream>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include "../Reader.h"

namespace Core {
namespace Json {
namespace DataMapper {

JsonFile::JsonFile(const std::string& path, Core::Json::JsonConverter& converter) : 
path(path), converter(converter) {}

JsonFile JsonFile::fromPath(const std::string& path) {
    Core::Json::Reader reader;
    Core::Json::JsonConverter converter(reader);
    JsonFile data_mapper(path, converter);
    return data_mapper;
}

const std::string& JsonFile::getPath() const {
    return path;
}

JsonFile& JsonFile::setPath(const std::string& path) {
    this->path = path;
    return *this;
}

const Core::Json::JsonConverter& JsonFile::getConverter() const {
    return converter;
}

JsonFile& JsonFile::store(const std::vector<Sensor*> sensor) {
    QJsonArray json_items;
    for (
        std::vector<Sensor*>::const_iterator it = sensor.begin();
        it != sensor.end();
        it++
    ) {
        json_items.push_back(converter.fromObject(**it));
    }
    QJsonDocument document(json_items);
    QFile json_file(path.c_str());
    json_file.open(QFile::WriteOnly);
    json_file.write(document.toJson());
    json_file.close();
    return *this;
}

std::vector<Sensor*> JsonFile::load() {
    std::vector<Sensor*> sensor;
    QFile json_file(path.c_str());
    json_file.open(QFile::ReadOnly);
    QByteArray data = json_file.readAll();
    json_file.close();
    QJsonDocument document = QJsonDocument::fromJson(data);
    QJsonArray json_items = document.array();

    for (const QJsonValue& value: json_items) {
        QJsonObject json_object = value.toObject();
        sensor.push_back(converter.toObject(json_object));
    }
    return sensor;
}

}
}
}