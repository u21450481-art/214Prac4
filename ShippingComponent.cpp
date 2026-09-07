#include "ShippingComponent.h"

#include "DestinationIterator.h"
#include "BFSIterator.h"
#include "CostFilterIterator.h"

ShippingComponent::ShippingComponent(double weight, double cost, const std::string &destination,
                                     int deliveryTime)
    : weight(weight), cost(cost), destination(destination), deliveryTime(deliveryTime),
      timeRemaining(deliveryTime)
{
}

ShippingComponent::~ShippingComponent()
{
}

void ShippingComponent::Add(ShippingComponent *c)
{
    (void)c;
}

void ShippingComponent::Remove(ShippingComponent *c)
{
    (void)c;
}

ShippingComponent *ShippingComponent::GetChild(int index)
{
    (void)index;
    return NULL;
}

double ShippingComponent::getWeight() const
{
    return this->weight;
}

double ShippingComponent::getCost() const
{
    return this->cost;
}

std::string ShippingComponent::getDestination() const
{
    return this->destination;
}

int ShippingComponent::getDeliveryTime() const
{
    return this->deliveryTime;
}

void ShippingComponent::setDeliveryTime(int deliveryTime)
{
    this->deliveryTime = deliveryTime;
}

int ShippingComponent::getTimeRemaining() const
{
    return this->timeRemaining;
}

/* Leaf behaviour: one day off this component's own countdown, never past zero. */
void ShippingComponent::advanceDay()
{
    if (this->timeRemaining > 0)
    {
        this->timeRemaining--;
    }
}

// factory methods to make iterators:
Iterator *ShippingComponent::createBFSIterator()
{
    return new BFSIterator(this);
}

Iterator *ShippingComponent::createDestinationIterator(const std::string &dest)
{
    return new DestinationIterator(this, dest);
}

Iterator *ShippingComponent::createCostFilterIterator(double threshold)
{
    return new CostFilterIterator(this, threshold);
}