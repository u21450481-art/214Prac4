#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>

#include "ShippingComponent.h"

class Package : public ShippingComponent {

    public:
        Package(double weight, double cost, const std::string& destination);

        virtual ~Package();

        virtual void Operation();
};

#endif
