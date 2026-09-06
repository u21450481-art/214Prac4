#include "Fragile.h"

Fragile::Fragile(ShippingComponent* component) : PackageDecorator(component) {
}

std::string Fragile::typeName() const {
    return "Fragile";
}

double Fragile::getWeight() const {
    return PackageDecorator::getWeight() + 1.5;
}

double Fragile::getCost() const {
    return PackageDecorator::getCost() + 25.0;
}

int Fragile::getDeliveryTime() const {
    return PackageDecorator::getDeliveryTime() + 1;
}
