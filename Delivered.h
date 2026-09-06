#ifndef DELIVERED_H
#define DELIVERED_H

#include "PackageState.h"

class Delivered : public PackageState { //concreteState
    public:
        std::string name() const override;
};

//delivered is the final state and hence cannot trastition to another state

#endif
