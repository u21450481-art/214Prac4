#ifndef FRAGILE_H
#define FRAGILE_H

#include "PackageDecorator.h"

class Fragile : public PackageDecorator { //ConcreteDecorator

    protected:
        std::string typeName() const override;

    public:
        Fragile(ShippingComponent* component);
};

#endif
