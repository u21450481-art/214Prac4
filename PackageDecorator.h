#ifndef PACKAGEDECORATOR_H
#define PACKAGEDECORATOR_H

#include <string>

#include "ShippingComponent.h"

class PackageDecorator : public ShippingComponent
{ // AbstarctDecorator

protected:
    ShippingComponent *component;

    PackageDecorator(ShippingComponent *component);
    virtual std::string typeName() const = 0;

public:
    virtual ~PackageDecorator();

    // component functionality
    virtual void Operation();
    virtual void Add(ShippingComponent *c);
    virtual void Remove(ShippingComponent *c);
    //    virtual Iterator *createIterator();

    // getters
    virtual ShippingComponent *GetChild(int index);
    virtual double getWeight() const;
    virtual double getCost() const;
    virtual std::string getDestination() const;
    virtual int getDeliveryTime() const;
    virtual int getTimeRemaining() const;
    virtual void advanceDay();

    // setters
    virtual void setDeliveryTime(int deliveryTime);

    // decorators wrap the aggregate

    virtual Iterator *createBFSIterator() override;
    virtual Iterator *createDestinationIterator(const std::string &destination) override;
};

// ConcreteDecorators have added Cost, Weight and deliveryTime (in the getters) to simulate extra care and manpower required to handle said packages

#endif
