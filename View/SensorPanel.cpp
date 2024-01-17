#include "SensorPanel.h"
#include <QHBoxLayout>
#include <QPixmap>

namespace View
{
    SensorPanel::SensorPanel(Core::Sensor& sensor, QWidget* parent) : sensor(sensor), QWidget(parent)
    {
        QHBoxLayout* layout = new QHBoxLayout();
        layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

        QPixmap image(":Assets/" + QString::fromStdString(sensor.getType()) + ".png");

        artwork = new QLabel();
        artwork->setPixmap(image.scaledToHeight(256));
        layout->addWidget(artwork);

        info = new Info(sensor, this);
        info->show();
        layout->addWidget(info);

        connect(this, &SensorPanel::mousePressEvent, this, &SensorPanel::openViewer);
    }

    Core::Sensor* SensorPanel::getSensor()
    {
        return &sensor;
    }

    void SensorPanel::openViewer()
    {
        //scrollbar->openViewer(sensor);
    }
};