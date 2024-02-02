#include "Results.h"

#include <QVBoxLayout>

namespace View
{
    Results::Results(std::vector<Core::Sensor*>& vector, QWidget* parent) : vector(vector), QWidget(parent)
    {
        std::cout << "Results::Results" << std::endl;
    }

    void Results::emitShowSensor(Core::Sensor& sensor)
    {
        std::cout << "Results::emitShowSensor" << std::endl;
        emit showSensor(&sensor);
    }

    void Results::emitEditSensor(Core::Sensor& sensor)
    {
        std::cout << "Results::emitEditSensor" << std::endl;
        emit editSensor(&sensor);
    }

    void Results::emitDeleteSensor(Core::Sensor& sensor)
    {
        std::cout << "Results::emitDeleteSensor" << std::endl;
        emit deleteSensor(&sensor);
    }

    void Results::showResults(std::vector<Core::Sensor*>& results_vector)
    {
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);


        std::cout << "Results::showResults dimensione vector = " << vector.size() << std::endl;
        std::cout << "Results::showResults dimensione results_vector = " << results_vector.size() << std::endl;

        std::cout << "Results::showResults Container non vuoto in showResult" << std::endl;
        if(!results_vector.empty())
            for(auto it = results_vector.begin(); it != results_vector.end(); it++)
            {
                std::cout << "Results::showResults Caricando i risultati..." << std::endl;
                Info* info = new Info(**it);
                container.push_back(info);
                std::cout << "Results::showResults Dimensione container di Info in showResults = " << container.size() << std::endl;
                layout->addWidget(container.last());

                connect(info, &Info::showSensor, this, &Results::emitShowSensor);
                connect(info, &Info::editSensor, this, &Results::emitEditSensor);
                connect(info, &Info::deleteSensor, this, &Results::emitDeleteSensor);
            }
    }

    std::vector<Core::Sensor*> Results::showResultsById(unsigned int id)
    {
        std::cout << "Results::showResultsById entrato in Results::receiveId" << std::endl;

        std::vector<Core::Sensor*> results_vector;

        if(!vector.empty())
        {
            for(auto it = vector.begin(); it != vector.end(); ++it)
            {
                std::cout << "Results::showResultsById entrato ciclo for Results::showResultsById" << std::endl;

                if(id == (*it)->getId())
                {
                    results_vector.push_back(*it);
                }
            }
        }
        else 
        {
            std::cout << "Results::showResultsById vector vuoto" << std::endl;
        }

        std::cout << "Results::showResultsById invocazione di Results::showResults" << std::endl;
        
        return results_vector;
    }

    std::vector<Core::Sensor*> Results::showResultsByFilter(std::string filter)
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
        // Invece che questo, devono passare un segnale con il vettore
        return results_vector;
    }
};