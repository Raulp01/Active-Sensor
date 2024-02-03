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

        // Crea i nuovi grafici per un tipo CaloriesCounter

        QLabel* bpm_label = new QLabel("Heart Sensor Chart: x-Time: h, y-Bpm");
        layout->addWidget(bpm_label);
        layout->addWidget(createBpmChart(calories_counter));
        
        QLabel* calories_label = new QLabel("Calories Chart: x-Time: h, y-Calories burned: kcal");
        layout->addWidget(calories_label);
        layout->addWidget(createCaloriesChart(calories_counter));
    }

    void ChartVisitor::visitActivity(const Core::Activity& activity)
    {
        widget = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
        widget->setLayout(layout);

        QLabel* bpm_label = new QLabel("Heart Sensor Chart: x-Time: h, y-Bpm");
        layout->addWidget(bpm_label);
        layout->addWidget(createBpmChart(activity));

        QLabel* calories_label = new QLabel("Calories Chart: x-Time: h, y-Calories burned: kcal");
        layout->addWidget(calories_label);
        layout->addWidget(createCaloriesChart(activity));

        QLabel* speed_label = new QLabel("Speedometer Chart: x-Time: h, y-Speed: km/h");
        layout->addWidget(speed_label);
        layout->addWidget(createSpeedChart(activity));
    }

    void ChartVisitor::visitHeartSensor(const Core::HeartSensor& heart_sensor)
    {
        widget = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);
        widget->setLayout(layout);

        QLabel* bpm_label = new QLabel("Heart Sensor Chart: x-Time: h, y-Bpm");
        layout->addWidget(bpm_label);
        layout->addWidget(createBpmChart(heart_sensor));
    }

    void ChartVisitor::visitSpeedometer(const Core::Speedometer& speedometer)
    {
        widget = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);
        widget->setLayout(layout);

        QLabel* speed_label = new QLabel("Speedometer Chart: x-Time: h, y-Speed: km/h");
        layout->addWidget(speed_label);
        layout->addWidget(createSpeedChart(speedometer));
    }

    QWidget* ChartVisitor::createCaloriesChart(const Core::CaloriesCounter& calories_counter)
    {   
        QChart* calories_chart = new QChart();
        QLineSeries* series_calories = new QLineSeries();

        if(calories_counter.getSensorVector().size() == calories_counter.getCaloriesVector().size())
        {
            /*
                Le dimensioni dei vettori vengono aumentate assieme in simulate(). 
                Prendo il vettore per l'asse delle x per realizzare il ciclo    
            */
            for(unsigned int i = 0; i < calories_counter.getSensorVector().size(); i++)
            {
                // Aggiunge un punto sul grafico per ogni elemento del vettore
                series_calories->append(calories_counter.getSensorVector()[i], calories_counter.getCaloriesVector()[i]);
            }
        }

        calories_chart->legend()->hide();
        calories_chart->addSeries(series_calories);

        QValueAxis* calories_x = new QValueAxis();
        calories_x->setRange(0, 12);
        calories_chart->addAxis(calories_x, Qt::AlignBottom);
        series_calories->attachAxis(calories_x);

        QValueAxis* calories_y = new QValueAxis();
        calories_y->setRange(0, 2000);
        calories_chart->addAxis(calories_y, Qt::AlignLeft);
        series_calories->attachAxis(calories_y);

        QChartView* calories_view = new QChartView(calories_chart);
        calories_view->setRenderHint(QPainter::Antialiasing);

        return calories_view;
    }

    QWidget* ChartVisitor::createBpmChart(const Core::HeartSensor& heart_sensor)
    {
        QChart* bpm_chart = new QChart();
        QLineSeries* series_bpm = new QLineSeries();

        if(heart_sensor.getSensorVector().size() == heart_sensor.getBpmVector().size())
        {
            for(unsigned int i = 0; i < heart_sensor.getSensorVector().size(); i++)
            {
                series_bpm->append(heart_sensor.getSensorVector()[i], heart_sensor.getBpmVector()[i]);
            }
        }

        bpm_chart->legend()->hide();
        bpm_chart->addSeries(series_bpm);

        QValueAxis* bpm_x = new QValueAxis();
        bpm_x->setRange(0, 12);
        bpm_chart->addAxis(bpm_x, Qt::AlignBottom);
        series_bpm->attachAxis(bpm_x);

        QValueAxis* bpm_y = new QValueAxis();
        bpm_y->setRange(0, 220);
        bpm_chart->addAxis(bpm_y, Qt::AlignLeft);
        series_bpm->attachAxis(bpm_y);

        QChartView* bpm_view = new QChartView(bpm_chart);
        bpm_view->setRenderHint(QPainter::Antialiasing);

        return bpm_view;
    }

    QWidget* ChartVisitor::createSpeedChart(const Core::Speedometer& speedometer)
    {
        QChart* speed_chart = new QChart();
        QLineSeries* series_speed = new QLineSeries();

        if(speedometer.getSensorVector().size() == speedometer.getSpeedVector().size())
        {
            for(unsigned int i = 0; i < speedometer.getSensorVector().size(); i++)
            {
                series_speed->append(speedometer.getSensorVector()[i], speedometer.getSpeedVector()[i]);
            }
        }

        speed_chart->legend()->hide();
        speed_chart->addSeries(series_speed);

        QValueAxis* speed_x = new QValueAxis();
        speed_x->setRange(0, 12);
        speed_chart->addAxis(speed_x, Qt::AlignBottom);
        series_speed->attachAxis(speed_x);

        QValueAxis* speed = new QValueAxis();
        speed->setRange(0, 40);
        speed_chart->addAxis(speed, Qt::AlignLeft);
        series_speed->attachAxis(speed);

        QChartView* speed_view = new QChartView(speed_chart);
        speed_view->setRenderHint(QPainter::Antialiasing);

        return speed_view;
    }
}