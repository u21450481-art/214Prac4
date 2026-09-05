#include "Package.h"

#include <iomanip>
#include <iostream>

Package::Package(double weight, double cost, const std::string& destination)
    : ShippingComponent(weight, cost, destination) {
}

Package::~Package() {
}

void Package::Operation() {
    std::cout << "Package -> " << this->destination
              << " | " << std::fixed << std::setprecision(2) << this->weight << " kg"
              << " | cost " << std::fixed << std::setprecision(2) << this->cost
              << std::endl;
}
