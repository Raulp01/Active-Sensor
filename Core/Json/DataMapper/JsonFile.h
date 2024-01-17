#ifndef JSONFILE
#define JSONFILE

#include <string>
#include <vector>

#include "../../Sensor.h"
#include "../JsonConverter.h"

namespace Core {
namespace Json {
namespace DataMapper {

class JsonFile {
  private:
    std::string path;
    Core::Json::JsonConverter& converter;

  public:
    JsonFile(const std::string& path, Core::Json::JsonConverter& converter);
    static JsonFile fromPath(const std::string& path);
    const std::string& getPath() const;
    JsonFile& setPath(const std::string& path);
    const Core::Json::JsonConverter& getConverter() const;
    JsonFile& store(const std::vector<Sensor*> sensor);
    std::vector<Sensor*> load();
};

}
}
}

#endif