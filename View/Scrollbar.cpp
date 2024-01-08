#include "../Core/Error.h"
#include "Scrollbar.h"

namespace View
{
    Scrollbar::Scrollbar(MainWindow* mainwindow, Core::Container& container, QWidget* parent) :
    mainwindow(mainwindow), container(container), QWidget(parent)
    {
        container.registerObserver(this);

        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

        content = new QWidget();

        QScrollArea* scroll_area = new QScrollArea();
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setWidgetResizable(true);
        scroll_area->setWidget(content);
        layout->addWidget(scroll_area);

        vector_layout = new QVBoxLayout(content);
        vector_layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    }

    void Scrollbar::notifyAdd(Core::Container& cont)
    {
        SensorPanel* sensor_panel = new SensorPanel(this, **(cont.begin()));

        panel_vector.push_back(sensor_panel);

        sensor_panel->show();
    }

    void Scrollbar::notifyRemove(Core::Container& cont, Core::Sensor& sensor)
    {
        auto it = panel_vector.begin();
        while((*it)->getSensor() != &sensor || it == panel_vector.end())
        {
            ++it;
        }
        if(*it)
        {
            panel_vector.erase(it);
        }
    }

    void Scrollbar::openViewer(Core::Sensor& sensor)
    {
        mainwindow->openViewer(sensor);
    }
};