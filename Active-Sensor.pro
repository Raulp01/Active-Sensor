######################################################################
# Automatically generated by qmake (3.1) Tue Jan 2 20:06:39 2024
######################################################################

TEMPLATE = app
TARGET = Active-Sensor
INCLUDEPATH += .
QT += widgets
QT += charts

QMAKE_CXXFLAGS_WARN_ON += -Wno-reorder

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += Core/Activity.h Core/CaloriesCounter.h Core/HeartSensor.h \
Core/Sensor.h Core/Speedometer.h IConstVisitor.h IVisitor.h \
View/Info.h View/InfoVisitor.h View/MainWindow.h View/Viewer.h View/ViewerVisitor.h View/Results.h\
Core/Json/DataMapper/JsonFile.h \
Core/Json/IReader.h Core/Json/Reader.h Core/Json/JsonVisitor.h Core/Json/JsonConverter.h \
View/Editor.h View/Search.h View/ChartVisitor.h

SOURCES += Core/Activity.cpp Core/CaloriesCounter.cpp Core/HeartSensor.cpp \
Core/Sensor.cpp Core/Speedometer.cpp View/Info.cpp View/InfoVisitor.cpp View/MainWindow.cpp View/Viewer.cpp View/ViewerVisitor.cpp  View/Results.cpp\
Core/Json/DataMapper/JsonFile.cpp \
Core/Json/Reader.cpp Core/Json/JsonVisitor.cpp Core/Json/JsonConverter.cpp \
View/Editor.cpp View/Search.cpp View/ChartVisitor.cpp\
main.cpp  

RESOURCES += resources.qrc
