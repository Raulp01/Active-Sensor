#include <QApplication>
#include "View/MainWindow.h"
#include <vector>
#include <iostream>
#include "Core/Sensor.h"
#include "Core/Json/Reader.h"
#include "Core/Json/JsonConverter.h"
#include "Core/Json/DataMapper/JsonFile.h"

int main(int argc, char* argv[])
{
    std::string path = "";
    std::vector<Core::Sensor*> vector;

    Core::Json::Reader reader;
    Core::Json::JsonConverter converter(reader);
    Core::Json::DataMapper::JsonFile file(path, converter);

    QApplication app(argc, argv);

    View::MainWindow main_window(vector, file);

    main_window.resize(1920,1080);

    main_window.show();

    return app.exec();
}