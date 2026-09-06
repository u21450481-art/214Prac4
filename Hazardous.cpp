#include "Hazardous.h"

Hazardous::Hazardous(ShippingComponent* component) : PackageDecorator(component) {
}

std::string Hazardous::typeName() const {
    return "Hazardous";
}

double Hazardous::getWeight() const {
    return PackageDecorator::getWeight() + 2.5;
}

double Hazardous::getCost() const {
    return PackageDecorator::getCost() + 45.0;
}

int Hazardous::getDeliveryTime() const {
    return PackageDecorator::getDeliveryTime() + 2;
}
