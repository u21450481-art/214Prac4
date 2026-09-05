#include "ShippingComponent.h"

#include "DestinationIterator.h"

ShippingComponent::ShippingComponent(double weight, double cost, const std::string& destination)
    : weight(weight), cost(cost), destination(destination) {
}

ShippingComponent::~ShippingComponent() {
}

void ShippingComponent::Add(ShippingComponent* c) {
    (void) c;
}

void ShippingComponent::Remove(ShippingComponent* c) {
    (void) c;
}

ShippingComponent* ShippingComponent::GetChild(int index) {
    (void) index;
    return NULL;
}

Iterator* ShippingComponent::createIterator() {
    return new DestinationIterator(this);
}
