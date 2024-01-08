#ifndef CONTAINER
#define CONTAINER

#include "Activity.h"
#include "../ContainerObserverInterface.h"
#include <vector>

namespace Core
{
    class Container
    {
        private:
        std::vector<ContainerObserverInterface*> observers;

        public:
        std::vector<Sensor*> vector;
        bool empty() const;
        unsigned int size() const;

        void registerObserver(ContainerObserverInterface* obs);

        // Metodi di aggiunta (in coda) e rimozione (accesso casuale)
        Container& add(Sensor* sensor);
        void remove(Sensor* sensor);
        std::vector<Sensor*>::iterator begin();
    };
};

#endif