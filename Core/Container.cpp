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
        for(auto it = vector.begin(); it != vector.end(); ++it)
        {
            if(*it == sensor)
            {
                vector.erase(it);
            }
        }

        for(auto observer = observers.begin(); observer != observers.end(); ++observer)
        {
            (*observer)->notifyRemove(*this);
        }

        //Da testare
    }
};