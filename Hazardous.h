#ifndef HAZARDOUS_H
#define HAZARDOUS_H

#include "PackageDecorator.h"

class Hazardous : public PackageDecorator { //ConcreteDecorator

    protected:
        std::string typeName() const override;

    public:
        Hazardous(ShippingComponent* component);
};

#endif
