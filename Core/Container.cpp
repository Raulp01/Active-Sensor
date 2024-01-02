#include "../Core/Container.h"

namespace Core
{
    bool Container::empty() const
    {
        return container.empty();
    }

    unsigned int Container::size() const
    {
        return container.size();
    }

    void Container::registerObserver(ContainerObserverInterface* obs)
    {
        observers.push_back(obs);
    }

    Container& Container::add(Sensor& sensor)
    {
        container.push_back(sensor);
        for(auto observer = observers.begin(); observer != observers.end(); ++observer)
        {
            (*observer)->notifyAdd(*this);
        }
    }

    void Container::remove(Sensor& sensor)
    {
        std::vector<Sensor&>::iterator it;
        *it = sensor;
        container.erase(it);

        for(auto observer = observers.begin(); observer != observers.end(); ++observer)
        {
            (*observer)->notifyRemove(*this);
        }

        //Da testare
    }
};