#ifndef SHIPMENTGROUP_H
#define SHIPMENTGROUP_H

#include <string>
#include <vector>

#include "ShippingComponent.h"

class ShipmentGroup : public ShippingComponent {

    private:
        std::vector<ShippingComponent*> children;

    public:
        ShipmentGroup(double weight, double cost, const std::string& destination);

        virtual ~ShipmentGroup();

        virtual void Operation();

        virtual void Add(ShippingComponent* c);
        virtual void Remove(ShippingComponent* c);
        virtual ShippingComponent* GetChild(int index);
};

#endif
