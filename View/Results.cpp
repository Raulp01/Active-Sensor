#include "Results.h"

#include <QVBoxLayout>

namespace View
{
    /*
        Classe usata per caricare i widget Info di tutti i sensori o dei sensori 
        cercati tramite id o filter
    */
    Results::Results(const std::vector<Core::Sensor*>& vector, QWidget* parent) : vector(vector), QWidget(parent) {}

    void Results::emitShowSensor(Core::Sensor& sensor)
    {
        emit showSensor(&sensor);
    }

    void Results::emitEditSensor(Core::Sensor& sensor)
    {
        emit editSensor(&sensor);
    }

    void Results::emitDeleteSensor(const Core::Sensor& sensor)
    {
        emit deleteSensor(&sensor);
    }

    void Results::showResults(const std::vector<Core::Sensor*>& results_vector)
    {
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

        if(!results_vector.empty())
            for(auto it = results_vector.begin(); it != results_vector.end(); it++)
            {
                Info* info = new Info(**it);
                container.push_back(info);

                layout->addWidget(container.last());

                connect(info, &Info::showSensor, this, &Results::emitShowSensor);
                connect(info, &Info::editSensor, this, &Results::emitEditSensor);
                connect(info, &Info::deleteSensor, this, &Results::emitDeleteSensor);
            }
    }

    const std::vector<Core::Sensor*> Results::showResultsById(unsigned int id)
    {
        std::vector<Core::Sensor*> results_vector;

        if(!vector.empty())
        {
            for(auto it = vector.begin(); it != vector.end(); ++it)
            {
                if(id == (*it)->getId())
                {
                    results_vector.push_back(*it);
                }
            }
        }
        
        return results_vector;
    }

    const std::vector<Core::Sensor*> Results::showResultsByFilter(std::string filter)
    {
        std::vector<Core::Sensor*> results_vector;

        if(!vector.empty()) 
        {
            for(auto it = vector.begin(); it != vector.end(); it++)
            {
                if((*it)->getType() == filter)
                {
                    results_vector.push_back(*it);
                }
            }
        }
        return results_vector;
    }
};