#ifndef REFRIDGERATED_H
#define REFRIDGERATED_H

#include "PackageDecorator.h"

class Refridgerated : public PackageDecorator { //ConcreteDecorator

    protected:
        std::string typeName() const override;

    public:
        Refridgerated(ShippingComponent* component);
};

#endif
