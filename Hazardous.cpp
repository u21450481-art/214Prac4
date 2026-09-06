#include "Hazardous.h"

Hazardous::Hazardous(ShippingComponent* component) : PackageDecorator(component) {
}

std::string Hazardous::typeName() const {
    return "Hazardous";
}
