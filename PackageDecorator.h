#ifndef PACKAGEDECORATOR_H
#define PACKAGEDECORATOR_H

#include <string>

#include "ShippingComponent.h"

class PackageDecorator : public ShippingComponent { //AbstarctDecorator

    protected:
        ShippingComponent* component;

        PackageDecorator(ShippingComponent* component);
        virtual std::string typeName() const = 0;

    public:
        virtual ~PackageDecorator();

        //component functionality
        virtual void Operation();
        virtual void Add(ShippingComponent* c);
        virtual void Remove(ShippingComponent* c);
        virtual Iterator* createIterator();

        //getters
        virtual ShippingComponent* GetChild(int index);
        virtual double getWeight() const;
        virtual double getCost() const;
        virtual std::string getDestination() const;
        virtual int getDeliveryTime() const;

        //setters
        virtual void setDeliveryTime(int deliveryTime);
};

#endif
