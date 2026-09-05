#include "ShipmentGroup.h"

#include <iomanip>
#include <iostream>

ShipmentGroup::ShipmentGroup(double weight, double cost, const std::string& destination)
    : ShippingComponent(weight, cost, destination), children() {
}

ShipmentGroup::~ShipmentGroup() {
    for (unsigned int i = 0; i < this->children.size(); i++) {
        delete this->children[i];
    }
    this->children.clear();
}

void ShipmentGroup::Operation() {
    std::cout << "ShipmentGroup -> " << this->destination
              << " | " << this->children.size() << " item(s)"
              << " | " << std::fixed << std::setprecision(2) << this->weight << " kg"
              << " | cost " << std::fixed << std::setprecision(2) << this->cost
              << std::endl;

    for (unsigned int i = 0; i < this->children.size(); i++) {
        this->children[i]->Operation();
    }
}

void ShipmentGroup::Add(ShippingComponent* c) {
    if (c == NULL || c == this) {
        return;
    }
    this->children.push_back(c);
}

void ShipmentGroup::Remove(ShippingComponent* c) {
    for (unsigned int i = 0; i < this->children.size(); i++) {
        if (this->children[i] == c) {
            this->children.erase(this->children.begin() + i);
            return;
        }
    }
}

ShippingComponent* ShipmentGroup::GetChild(int index) {
    if (index < 0 || index >= (int) this->children.size()) {
        return NULL;
    }
    return this->children[index];
}
