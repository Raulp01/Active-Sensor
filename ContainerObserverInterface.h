#ifndef OBSERVER
#define OBSERVER

#include "Core/Container.h"

namespace Core {

class Container;

class ContainerObserverInterface
{
    public:
    virtual void notifyAdd(Container& container) = 0;
    virtual void notifyRemove(Container& container) = 0;
    virtual ~ContainerObserverInterface() = default;
};
};

#endif