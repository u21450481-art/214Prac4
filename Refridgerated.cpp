#include "Refridgerated.h"

Refridgerated::Refridgerated(ShippingComponent* component) : PackageDecorator(component) {
}

std::string Refridgerated::typeName() const {
    return "Refridgerated";
}

double Refridgerated::getWeight() const {
    return PackageDecorator::getWeight() + 3.0;
}

double Refridgerated::getCost() const {
    return PackageDecorator::getCost() + 35.0;
}

int Refridgerated::getDeliveryTime() const {
    return PackageDecorator::getDeliveryTime() + 1;
}
