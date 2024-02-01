#include "ChartVisitor.h"
#include <QtCharts/QtCharts>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QVBoxLayout>
#include <QLabel>

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
        layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);
        widget->setLayout(layout);

        QLabel* bpm_label = new QLabel("Heart Sensor Chart: x-time, y-bpm");
        layout->addWidget(bpm_label);

        QChart* bpm_chart = new QChart();
        QLineSeries* series_bpm = new QLineSeries();

        for(
            auto it_t = calories_counter.getSensorVector().begin(); 
            it_t != calories_counter.getSensorVector().end(); it_t++
        )
        {
            for
            (
                auto it_b = calories_counter.getBpmVector().begin();
                it_b != calories_counter.getBpmVector().end(); it_b++
            )
            {
                series_bpm->append(*it_t, *it_b);
            }       
        }

        bpm_chart->legend()->hide();
        bpm_chart->addSeries(series_bpm);

        QValueAxis* bpm_x = new QValueAxis();
        bpm_x->setRange(0, 24);
        bpm_chart->addAxis(bpm_x, Qt::AlignBottom);
        series_bpm->attachAxis(bpm_x);

        QValueAxis* bpm_y = new QValueAxis();
        bpm_y->setRange(0, 200);
        bpm_chart->addAxis(bpm_y, Qt::AlignLeft);
        series_bpm->attachAxis(bpm_y);

        QChartView* bpm_view = new QChartView(bpm_chart);
        bpm_view->setRenderHint(QPainter::Antialiasing);

        layout->addWidget(bpm_view);

        QLabel* calories_label = new QLabel("Calories Chart: x-time, y-calories burned");
        layout->addWidget(calories_label);

        QChart* calories_chart = new QChart();
        QLineSeries* series_calories = new QLineSeries();

        for(auto it_t = calories_counter.getSensorVector().begin(); it_t != calories_counter.getSensorVector().end(); it_t++) 
        {
            for(auto it_c = calories_counter.getCaloriesVector().begin(); it_c != calories_counter.getCaloriesVector().end(); it_c++)
            {
                series_calories->append(*it_t, *it_c);
            }       
        }

        calories_chart->legend()->hide();
        calories_chart->addSeries(series_calories);

        QValueAxis* calories_x = new QValueAxis();
        calories_x->setRange(0, 24);
        calories_chart->addAxis(calories_x, Qt::AlignBottom);
        series_calories->attachAxis(calories_x);

        QValueAxis* calories_y = new QValueAxis();
        calories_y->setRange(0, 2000);
        calories_chart->addAxis(calories_y, Qt::AlignLeft);
        series_calories->attachAxis(calories_y);

        QChartView* calories_view = new QChartView(calories_chart);
        calories_view->setRenderHint(QPainter::Antialiasing);

        layout->addWidget(calories_view);
    }

    void ChartVisitor::visitActivity(const Core::Activity& activity)
    {
        widget = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
        widget->setLayout(layout);

        QLabel* bpm_label = new QLabel("Heart Sensor Chart: x-time, y-bpm");
        layout->addWidget(bpm_label);

        // Creazione del grafico per i bpm

        QChart* bpm_chart = new QChart();
        QLineSeries* series_bpm = new QLineSeries();

        // Iterazione sugli elementi che andranno a comporre l'asse x
        for(auto it_t = activity.getSensorVector().begin(); it_t != activity.getSensorVector().end(); it_t++)
        {   
            // Iterazione sugli elementi che andranno a comporre l'asse y
            for(auto it_b = activity.getBpmVector().begin(); it_b != activity.getBpmVector().end(); it_b++)
            {
                series_bpm->append(*it_t, *it_b);
            }       
        }

        bpm_chart->legend()->hide();
        bpm_chart->addSeries(series_bpm);

        // Creazione asse x con range da 0 a 24
        QValueAxis* bpm_x = new QValueAxis();
        bpm_x->setRange(0, 24);
        bpm_chart->addAxis(bpm_x, Qt::AlignBottom);
        series_bpm->attachAxis(bpm_x);

        // Creazione asse y con range da 0 a 200
        QValueAxis* bpm_y = new QValueAxis();
        bpm_y->setRange(0, 200);
        bpm_chart->addAxis(bpm_y, Qt::AlignLeft);
        series_bpm->attachAxis(bpm_y);

        // Creazione vista del grafico
        QChartView* bpm_view = new QChartView(bpm_chart);
        bpm_view->setRenderHint(QPainter::Antialiasing);

        layout->addWidget(bpm_view);

        QLabel* calories_label = new QLabel("Calories Chart: x-time, y-calories burned");
        layout->addWidget(calories_label);

        QChart* calories_chart = new QChart();
        QLineSeries* series_calories = new QLineSeries();

        for(auto it_t = activity.getSensorVector().begin(); it_t != activity.getSensorVector().end(); it_t++)
        {
            for(auto it_c = activity.getCaloriesVector().begin(); it_c != activity.getCaloriesVector().end(); it_c++)
            {
                series_calories->append(*it_t, *it_c);
            }       
        }

        calories_chart->legend()->hide();
        calories_chart->addSeries(series_calories);

        QValueAxis* calories_x = new QValueAxis();
        calories_x->setRange(0, 24);
        calories_chart->addAxis(calories_x, Qt::AlignBottom);
        series_calories->attachAxis(calories_x);

        QValueAxis* calories_y = new QValueAxis();
        calories_y->setRange(0, 2000);
        calories_chart->addAxis(calories_y, Qt::AlignLeft);
        series_calories->attachAxis(calories_y);

        QChartView* calories_view = new QChartView(calories_chart);
        calories_view->setRenderHint(QPainter::Antialiasing);

        layout->addWidget(calories_view);

        QLabel* speed_label = new QLabel("Speedometer Chart: x-distance, y-avarage speed");
        layout->addWidget(speed_label);

        QChart* speed_chart = new QChart();
        QLineSeries* series_speed = new QLineSeries();

        for(auto it_d = activity.getDistanceVector().begin(); it_d != activity.getDistanceVector().end(); it_d++)
        {
            for(auto it_s = activity.getSpeedVector().begin(); it_s != activity.getSpeedVector().end(); it_s++)
            {
                series_speed->append(*it_d, *it_s);
            }       
        }

        speed_chart->legend()->hide();
        speed_chart->addSeries(series_speed);

        QValueAxis* distance = new QValueAxis();
        distance->setRange(0, 50);
        speed_chart->addAxis(distance, Qt::AlignBottom);
        series_speed->attachAxis(distance);

        QValueAxis* speed = new QValueAxis();
        speed->setRange(0, 40);
        speed_chart->addAxis(speed, Qt::AlignLeft);
        series_speed->attachAxis(speed);

        QChartView* speed_view = new QChartView(speed_chart);
        speed_view->setRenderHint(QPainter::Antialiasing);

        layout->addWidget(speed_view);
    }

    void ChartVisitor::visitHeartSensor(const Core::HeartSensor& heart_sensor)
    {
        widget = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);
        widget->setLayout(layout);

        QLabel* bpm_label = new QLabel("Heart Sensor Chart: x-time, y-bpm");
        layout->addWidget(bpm_label);

        QChart* bpm_chart = new QChart();
        QLineSeries* series_bpm = new QLineSeries();

        for(auto it_t = heart_sensor.getSensorVector().begin(); it_t != heart_sensor.getSensorVector().end(); it_t++)
        {
            for(auto it_b = heart_sensor.getBpmVector().begin(); it_b != heart_sensor.getBpmVector().end(); it_b++)
            {
                series_bpm->append(*it_t, *it_b);
            }       
        }

        bpm_chart->legend()->hide();
        bpm_chart->addSeries(series_bpm);

        QValueAxis* bpm_x = new QValueAxis();
        bpm_x->setRange(0, 24);
        bpm_chart->addAxis(bpm_x, Qt::AlignBottom);
        series_bpm->attachAxis(bpm_x);

        QValueAxis* bpm_y = new QValueAxis();
        bpm_y->setRange(0, 200);
        bpm_chart->addAxis(bpm_y, Qt::AlignLeft);
        series_bpm->attachAxis(bpm_y);

        QChartView* bpm_view = new QChartView(bpm_chart);
        bpm_view->setRenderHint(QPainter::Antialiasing);

        layout->addWidget(bpm_view);
    }

    void ChartVisitor::visitSpeedometer(const Core::Speedometer& speedometer)
    {
        widget = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);
        widget->setLayout(layout);

        QLabel* speed_label = new QLabel("Speedometer Chart: x-distance, y-avarage speed");
        layout->addWidget(speed_label);

        QChart* speed_chart = new QChart();
        QLineSeries* series_speed = new QLineSeries();

        for(auto it_d = speedometer.getDistanceVector().begin(); it_d != speedometer.getDistanceVector().end(); it_d++)
        {
            for(auto it_s = speedometer.getSpeedVector().begin(); it_s != speedometer.getSpeedVector().end(); it_s++)
            {
                series_speed->append(*it_d, *it_s);
            }       
        }

        speed_chart->legend()->hide();
        speed_chart->addSeries(series_speed);

        QValueAxis* distance = new QValueAxis();
        distance->setRange(0, 50);
        speed_chart->addAxis(distance, Qt::AlignBottom);
        series_speed->attachAxis(distance);

        QValueAxis* speed = new QValueAxis();
        speed->setRange(0, 40);
        speed_chart->addAxis(speed, Qt::AlignLeft);
        series_speed->attachAxis(speed);

        QChartView* speed_view = new QChartView(speed_chart);
        speed_view->setRenderHint(QPainter::Antialiasing);

        layout->addWidget(speed_view);
    }
}