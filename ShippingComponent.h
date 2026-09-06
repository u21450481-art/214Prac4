#ifndef SHIPPINGCOMPONENT_H
#define SHIPPINGCOMPONENT_H

#include <string>

class Iterator;

class ShippingComponent {

    protected:
        double weight;
        double cost;
        std::string destination;
        int deliveryTime;

        ShippingComponent(double weight, double cost, const std::string& destination,
                          int deliveryTime);

    public:
        virtual ~ShippingComponent();

        virtual void Operation() = 0;

        virtual void Add(ShippingComponent* c);
        virtual void Remove(ShippingComponent* c);
        virtual ShippingComponent* GetChild(int index);
        virtual Iterator* createIterator();

        virtual double getWeight() const;
        virtual double getCost() const;
        virtual std::string getDestination() const;
        virtual int getDeliveryTime() const;
        virtual void setDeliveryTime(int deliveryTime);
};

#endif
