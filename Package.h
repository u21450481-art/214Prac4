#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>

#include "ShippingComponent.h"

class Package : public ShippingComponent
{

public:
    Package(double weight, double cost, const std::string &destination, int deliveryTime);

    virtual ~Package();

    virtual void Operation();

    virtual Iterator *createBFSIterator() override;
    virtual Iterator *createDestinationIterator(const std::string &destination) override;
};

#endif
