#include "ShippingComponent.h"

#include "DestinationIterator.h"

ShippingComponent::ShippingComponent(double weight, double cost, const std::string& destination,
                                     int deliveryTime)
    : weight(weight), cost(cost), destination(destination), deliveryTime(deliveryTime) {
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

double ShippingComponent::getWeight() const {
    return this->weight;
}

double ShippingComponent::getCost() const {
    return this->cost;
}

std::string ShippingComponent::getDestination() const {
    return this->destination;
}

int ShippingComponent::getDeliveryTime() const {
    return this->deliveryTime;
}

void ShippingComponent::setDeliveryTime(int deliveryTime) {
    this->deliveryTime = deliveryTime;
}
