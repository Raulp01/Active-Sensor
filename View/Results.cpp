#include "Results.h"

#include <QVBoxLayout>
#include <QScrollArea>

namespace View
{
    Results::Results(std::vector<Core::Sensor*>& vector, QWidget* parent) : vector(vector), QWidget(parent)
    {
        QScrollArea* scroll = new QScrollArea();
        scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll->setWidgetResizable(true);

        layout = new QVBoxLayout(scroll);
        layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

        refresh();

        connect(this, &Results::searchId, this, &Results::showResults);
    }

    void Results::clear()
    {
        if(container.isEmpty() == false)
        {
            //Pulizia
            while(container.count())
            {
                layout->removeWidget(container.takeLast());
                delete container.takeLast();
            }
        }
    }

    void Results::refresh()
    {
        clear();
        
        if(vector.empty() == false)
        {
            for(auto it = vector.begin(); it != vector.end(); ++it)
            {
                Info* info = new Info(**it);
                container.push_back(info);
                layout->addWidget(container.takeLast());

                connect(info->getOpenButton(), SIGNAL(pressed()), this, SLOT(emitShowSensor(*it)));
                connect(info->getEditButton(), SIGNAL(pressed()), this, SLOT(emitEditSensor(*it)));
                connect(info->getRemoveButton(), SIGNAL(pressed()), this, SLOT(emitDeleteSensor(*it)));
            }
        }
    }

    void Results::emitShowSensor(Core::Sensor* sensor)
    {
        emit showSensor(sensor);
    }

    void Results::emitEditSensor(Core::Sensor* sensor)
    {
        emit editSensor(sensor);
    }

    void Results::emitDeleteSensor(Core::Sensor* sensor)
    {
        emit deleteSensor(sensor);
    }

    void Results::showAll()
    {
        refresh();
    }

    void Results::showResults(std::vector<Core::Sensor*>& results_vector)
    {
        clear();

        if(results_vector.empty() == false)
        {
            for(auto it = results_vector.begin(); it != results_vector.end(); ++it)
            {
                Info* info = new Info(**it);
                container.push_back(info);
                layout->addWidget(container.takeLast());

                connect(info->getOpenButton(), SIGNAL(pressed()), this, SIGNAL(showSensor(*it)));
                connect(info->getEditButton(), SIGNAL(pressed()), this, SIGNAL(editSensor(*it)));
                connect(info->getRemoveButton(), SIGNAL(pressed()), this, SIGNAL(deleteSensor(*it)));
            }
        }
    }

    void Results::showResultsById(unsigned int id)
    {
        std::cout << "entrato in Results::receiveId" << std::endl;

        std::vector<Core::Sensor*> results_vector;

        std::vector<unsigned int> vector_id_input = convertId(id);

        for(auto it = vector.begin(); it != vector.end(); ++it)
        {
            std::vector<unsigned int> vector_id_sensor =convertId((**it).getId());

            auto id_it = vector_id_input.begin();
            bool match = true;

            while(id_it != vector_id_input.end() || match == true)
            {
                if(vector_id_sensor[*id_it] == *id_it)
                {
                    id_it++;
                }
                else
                {
                    match = false;
                }
            }

            if(id_it == vector_id_input.end())
            {
                results_vector.push_back(*it);
            }
        }

        emit searchId(results_vector);
    }

    std::vector<unsigned int> Results::convertId(unsigned int id)
    {
        std::vector<unsigned int> vector_id;

        while (true)
        {
            vector_id.insert(vector_id.begin(), id % 10);
            id /= 10;
            if(id == 0)
            {
                return vector_id;
            }
        }
    }
};