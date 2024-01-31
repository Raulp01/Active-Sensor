#include "ChartVisitor.h"
#include <QtCharts/QtCharts>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QVBoxLayout>

namespace View
{
    QWidget* ChartVisitor::getWidget()
    {
        return widget;
    }

    void ChartVisitor::visitCaloriesCounter(const Core::CaloriesCounter& calories_counter)
    {
        widget = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
        widget->setLayout(layout);


    }

    void ChartVisitor::visitActivity(const Core::Activity& activity)
    {
        widget = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
        widget->setLayout(layout);
    }

    void ChartVisitor::visitHeartSensor(const Core::HeartSensor& heart_sensor)
    {
        widget = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
        widget->setLayout(layout);
    }

    void ChartVisitor::visitSpeedometer(const Core::Speedometer& speedometer)
    {
        widget = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
        widget->setLayout(layout);
    }
}