#include "Results.h"

#include <QVBoxLayout>

namespace View
{
    Results::Results(std::vector<Core::Sensor*>& vector, QWidget* parent) : vector(vector), QWidget(parent)
    {
        layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

        showResults(vector);
    }

    void Results::clear()
    {
        if(container.isEmpty() == false)
        {
            //Pulizia
            while(container.count())
            {
                std::cout << "Clearing previous data" << std::endl;
                layout->removeWidget(container.last());
                delete container.takeLast();
            }
        }
    }

    void Results::emitShowSensor()
    {
        Core::Sensor& sensor = container.last()->getSensor(); 
        emit showSensor(&sensor);
    }

    void Results::emitEditSensor()
    {
        Core::Sensor& sensor = container.last()->getSensor(); 
        emit editSensor(&sensor);
    }

    void Results::emitDeleteSensor()
    {
        Core::Sensor& sensor = container.last()->getSensor(); 
        emit deleteSensor(&sensor);
    }

    void Results::showResults(std::vector<Core::Sensor*>& results_vector)
    {
        clear();

        std::cout << "showResults dimensione vector = " << vector.size() << std::endl;
        std::cout << "showResults dimensione results_vector = " << results_vector.size() << std::endl;

        if(results_vector.empty() == false)
        {
            std::cout << "Container non vuoto in showResult" << std::endl;
            for(auto it = results_vector.begin(); it != results_vector.end(); it++)
            {
                std::cout << "Caricando i risultati..." << std::endl;
                Info* info = new Info(**it);
                container.push_back(info);
                layout->addWidget(container.last());

                connect(container.last()->getOpenButton(), &QPushButton::pressed, this, &Results::emitShowSensor);
                connect(container.last()->getEditButton(), &QPushButton::pressed, this, &Results::emitEditSensor);
                connect(container.last()->getRemoveButton(), &QPushButton::pressed, this, &Results::emitDeleteSensor);
            }
        }
    }

    void Results::showResultsById(unsigned int id)
    {
        clear();
        std::cout << "entrato in Results::receiveId" << std::endl;

        std::vector<Core::Sensor*> results_vector;

        std::string id_input_string = std::to_string(id);

        if(vector.empty())
        {
            std::cout << "showResultsById :: vector vuoto" << std::endl;
        }

        for(auto it = vector.begin(); it != vector.end(); ++it)
        {
            std::cout << "entrato ciclo for Results::showResultsById" << std::endl;

            std::string sensor_id_string = std::to_string((**it).getId());

            bool match = true;
            unsigned int i = 0;

            while(i != id_input_string.length() && match == true)
            {
                std::cout << "id_input_string["<< i << "] = " << id_input_string[i] << std::endl;
                std::cout << "sensor_id_string[" << i << "] = " << sensor_id_string[i] << std::endl;
                if(id_input_string[i] != sensor_id_string[i])
                {
                    match = false;
                }
                i++;
            }
            

            if(match==true)
            {
                results_vector.push_back(*it);
            }
        }

        showResults(results_vector);
    }
};