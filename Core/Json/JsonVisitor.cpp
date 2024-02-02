#include "JsonVisitor.h"

namespace Core {
namespace Json {

QJsonObject JsonVisitor::getObject() const 
{
    return object;
}

void JsonVisitor::visitCaloriesCounter(const CaloriesCounter& calories_counter)
{
    QJsonObject calories_counter_object;
    calories_counter_object.insert("type", QJsonValue::fromVariant(calories_counter.getType().c_str()));
    calories_counter_object.insert("id", QJsonValue::fromVariant(calories_counter.getId()));
    calories_counter_object.insert("name", QJsonValue::fromVariant(calories_counter.getName().c_str()));
    calories_counter_object.insert("description", QJsonValue::fromVariant(calories_counter.getDescription().c_str()));
    calories_counter_object.insert("age", QJsonValue::fromVariant(calories_counter.getAge()));
    calories_counter_object.insert("height", QJsonValue::fromVariant(calories_counter.getHeight()));
    calories_counter_object.insert("weight", QJsonValue::fromVariant(calories_counter.getWeight()));
    calories_counter_object.insert("training_type", QJsonValue::fromVariant(calories_counter.getTrainingType()));
    calories_counter_object.insert("training_time", QJsonValue::fromVariant(calories_counter.getTrainingTime()));
    calories_counter_object.insert("bpm", QJsonValue::fromVariant(calories_counter.getBpm()));
    calories_counter_object.insert("calories", QJsonValue::fromVariant(calories_counter.getCalories()));
    object = calories_counter_object;
}

void JsonVisitor::visitHeartSensor(const HeartSensor& heart_sensor)
{
    QJsonObject heart_sensor_object;
    heart_sensor_object.insert("type", QJsonValue::fromVariant(heart_sensor.getType().c_str()));
    heart_sensor_object.insert("id", QJsonValue::fromVariant(heart_sensor.getId()));
    heart_sensor_object.insert("name", QJsonValue::fromVariant(heart_sensor.getName().c_str()));
    heart_sensor_object.insert("description", QJsonValue::fromVariant(heart_sensor.getDescription().c_str()));
    heart_sensor_object.insert("age", QJsonValue::fromVariant(heart_sensor.getAge()));
    heart_sensor_object.insert("height", QJsonValue::fromVariant(heart_sensor.getHeight()));
    heart_sensor_object.insert("weight", QJsonValue::fromVariant(heart_sensor.getWeight()));
    heart_sensor_object.insert("training_type", QJsonValue::fromVariant(heart_sensor.getTrainingType()));
    heart_sensor_object.insert("training_time", QJsonValue::fromVariant(heart_sensor.getTrainingTime()));
    heart_sensor_object.insert("bpm", QJsonValue::fromVariant(heart_sensor.getBpm()));
    object = heart_sensor_object;
}

void JsonVisitor::visitSpeedometer(const Speedometer& speedometer)
{
    QJsonObject speedometer_object;
    speedometer_object.insert("type", QJsonValue::fromVariant(speedometer.getType().c_str()));
    speedometer_object.insert("id", QJsonValue::fromVariant(speedometer.getId()));
    speedometer_object.insert("name", QJsonValue::fromVariant(speedometer.getName().c_str()));
    speedometer_object.insert("description", QJsonValue::fromVariant(speedometer.getDescription().c_str()));
    speedometer_object.insert("age", QJsonValue::fromVariant(speedometer.getAge()));
    speedometer_object.insert("height", QJsonValue::fromVariant(speedometer.getHeight()));
    speedometer_object.insert("weight", QJsonValue::fromVariant(speedometer.getWeight()));
    speedometer_object.insert("training_type", QJsonValue::fromVariant(speedometer.getTrainingType()));
    speedometer_object.insert("training_time", QJsonValue::fromVariant(speedometer.getTrainingTime()));
    speedometer_object.insert("speed", QJsonValue::fromVariant(speedometer.getSpeed()));
    speedometer_object.insert("distance", QJsonValue::fromVariant(speedometer.getDistance()));
    object = speedometer_object;
}

void JsonVisitor::visitActivity(const Activity& activity)
{
    QJsonObject activity_object;
    activity_object.insert("type", QJsonValue::fromVariant(activity.getType().c_str()));
    activity_object.insert("id", QJsonValue::fromVariant(activity.getId()));
    activity_object.insert("name", QJsonValue::fromVariant(activity.getName().c_str()));
    activity_object.insert("description", QJsonValue::fromVariant(activity.getDescription().c_str()));
    activity_object.insert("age", QJsonValue::fromVariant(activity.getAge()));
    activity_object.insert("height", QJsonValue::fromVariant(activity.getHeight()));
    activity_object.insert("weight", QJsonValue::fromVariant(activity.getWeight()));
    activity_object.insert("training_type", QJsonValue::fromVariant(activity.getTrainingType()));
    activity_object.insert("training_time", QJsonValue::fromVariant(activity.getTrainingTime()));
    activity_object.insert("bpm", QJsonValue::fromVariant(activity.getBpm()));
    activity_object.insert("calories", QJsonValue::fromVariant(activity.getCalories()));
    activity_object.insert("speed", QJsonValue::fromVariant(activity.getSpeed()));
    activity_object.insert("distance", QJsonValue::fromVariant(activity.getDistance()));
    object = activity_object;
}

}
}