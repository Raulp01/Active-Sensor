#include "Container.h"

namespace Core
{
    bool Container::empty() const
    {
        return vector.empty();
    }

    unsigned int Container::size() const
    {
        return vector.size();
    }

    void Container::registerObserver(ContainerObserverInterface* obs)
    {
        observers.push_back(obs);
    }

    Container& Container::add(Sensor* sensor)
    {
        vector.push_back(sensor);
        for(auto observer = observers.begin(); observer != observers.end(); ++observer)
        {
            (*observer)->notifyAdd(*this);
        }

        return *this;
    }

    void Container::remove(Sensor* sensor)
    {
        // Prima notifico la rimozione in modo che la GUI sia aggiornata
        for(auto observer = observers.begin(); observer != observers.end(); ++observer)
        {
            (*observer)->notifyRemove(*this, *sensor);
        }

        // Poi elimino il sensore dal vector
        for(auto it = vector.begin(); it != vector.end(); ++it)
        {
            if(*it == sensor)
            {
                vector.erase(it);
            }
        }

        //Da testare
    }

    std::vector<Sensor*>::iterator Container::begin()
    {
        return vector.begin();
    }
};