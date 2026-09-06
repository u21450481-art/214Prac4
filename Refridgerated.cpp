#include "Refridgerated.h"

Refridgerated::Refridgerated(ShippingComponent* component)
    : PackageDecorator(component) {
}

std::string Refridgerated::typeName() const {
    return "Refridgerated";
}
