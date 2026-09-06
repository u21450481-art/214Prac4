#include "Package.h"

#include "BFSIterator.h"
#include "DestinationIterator.h"
#include <iomanip>
#include <iostream>

Package::Package(double weight, double cost, const std::string &destination, int deliveryTime)
    : ShippingComponent(weight, cost, destination, deliveryTime)
{
}

Package::~Package()
{
}

void Package::Operation()
{
    std::cout << "Package -> " << getDestination()
              << " | " << std::fixed << std::setprecision(2) << getWeight() << " kg"
              << " | cost " << std::fixed << std::setprecision(2) << getCost()
              << " | " << getDeliveryTime() << " days"
              << std::endl;
}

Iterator *Package::createBFSIterator()
{
    return new BFSIterator(this);
}

Iterator *Package::createDestinationIterator(const std::string &destination)
{
    return new DestinationIterator(this, destination);
}