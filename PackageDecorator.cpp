#include "PackageDecorator.h"

#include <iostream>

// all  operations call the components operations of the same name adding null checks

PackageDecorator::PackageDecorator(ShippingComponent *component) : ShippingComponent(0.0, 0.0, "", 0), component(component)
{
}

PackageDecorator::~PackageDecorator()
{
    delete this->component;
}

void PackageDecorator::Operation()
{
    std::cout << this->typeName() << " package" << std::endl;

    if (this->component != NULL)
    {
        this->component->Operation();
    }
}

void PackageDecorator::Add(ShippingComponent *c)
{
    if (this->component != NULL)
    {
        this->component->Add(c);
    }
}

void PackageDecorator::Remove(ShippingComponent *c)
{
    if (this->component != NULL)
    {
        this->component->Remove(c);
    }
}

ShippingComponent *PackageDecorator::GetChild(int index)
{
    if (this->component == NULL)
    {
        return NULL;
    }
    return this->component->GetChild(index);
}

// Iterator *PackageDecorator::createIterator()
// {
//     if (this->component == NULL)
//     {
//         return NULL;
//     }
//     return this->component->createIterator();
// }

double PackageDecorator::getWeight() const
{
    return this->component == NULL ? 0.0 : this->component->getWeight();
}

double PackageDecorator::getCost() const
{
    return this->component == NULL ? 0.0 : this->component->getCost();
}

std::string PackageDecorator::getDestination() const
{
    return this->component == NULL ? std::string() : this->component->getDestination();
}

int PackageDecorator::getDeliveryTime() const
{
    return this->component == NULL ? 0 : this->component->getDeliveryTime();
}

int PackageDecorator::getTimeRemaining() const
{
    return this->component == NULL ? 0 : this->component->getTimeRemaining();
}

void PackageDecorator::advanceDay()
{
    if (this->component != NULL)
    {
        this->component->advanceDay();
    }
}

void PackageDecorator::setDeliveryTime(int deliveryTime)
{
    if (this->component != NULL)
    {
        this->component->setDeliveryTime(deliveryTime);
    }
}
Iterator *PackageDecorator::createBFSIterator()
{
    return component ? component->createBFSIterator() : nullptr;
}

Iterator *PackageDecorator::createDestinationIterator(const std::string &dest)
{
    return component ? component->createDestinationIterator(dest) : nullptr;
}

Iterator *PackageDecorator::createCostFilterIterator(double threshold)
{
    return component ? component->createCostFilterIterator(threshold) : nullptr;
}
