#ifndef SHIPPINGCOMPONENT_H
#define SHIPPINGCOMPONENT_H

#include <string>

class Iterator;

class ShippingComponent {

    protected:
        double weight;
        double cost;
        std::string destination;

        ShippingComponent(double weight, double cost, const std::string& destination);

    public:
        virtual ~ShippingComponent();

        virtual void Operation() = 0;

        virtual void Add(ShippingComponent* c);
        virtual void Remove(ShippingComponent* c);
        virtual ShippingComponent* GetChild(int index);
        virtual Iterator* createIterator();
};

#endif
