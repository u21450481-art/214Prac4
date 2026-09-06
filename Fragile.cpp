#include "Fragile.h"

Fragile::Fragile(ShippingComponent* component) : PackageDecorator(component) {
}

std::string Fragile::typeName() const
{
    return "Fragile";
}
