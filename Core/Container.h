#ifndef CONTAINER
#define CONTAINER

#include "../Core/Activity.h"
#include "../ContainerObserverInterface.h"
#include <vector>

namespace Core
{
    class Container
    {
        private:
        std::vector<Sensor&> container;
        std::vector<ContainerObserverInterface*> observers;

        public:
        bool empty() const;
        unsigned int size() const;

        void registerObserver(ContainerObserverInterface* obs);

        // Metodi di aggiunta (in coda) e rimozione (accesso casuale)
        Container& add(Sensor& sensor);
        void remove(Sensor& sensor);
    };
};

#endif