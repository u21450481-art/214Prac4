#include "PackageJourney.h"

#include <iostream>

#include "NotDelivered.h"
#include "ShippingComponent.h"

PackageJourney::PackageJourney(ShippingComponent* package) : package(package), state(new NotDelivered()) {
}

PackageJourney::~PackageJourney() 
{
    delete this->state;
}

void PackageJourney::changeState(PackageState* nextState) 
{
    if (this->package == NULL || nextState == NULL) {
        std::cout << "Error: cannot change state without a package." << std::endl;
        delete nextState;
        return;
    }

    delete this->state;
    this->state = nextState;

    std::cout << "Package state: " << this->status() << std::endl;
}

//calls the current states matching transition

void PackageJourney::dispatch() {
    this->state->dispatch(*this);
}

void PackageJourney::delay() {
    this->state->delay(*this);
}

void PackageJourney::resume() {
    this->state->resume(*this);
}

void PackageJourney::deliver() {
    this->state->deliver(*this);
}


//used as guards for state transitions
void PackageJourney::advanceDay() {
    if (this->package != NULL && this->package->getDeliveryTime() > 0)
    {
        this->package->setDeliveryTime(this->package->getDeliveryTime() - 1);
    }

    this->checkDeliveryTime();
}

void PackageJourney::checkDeliveryTime() {
    this->state->checkDeliveryTime(*this);
}

std::string PackageJourney::status() const {
    return this->state->name();
}

void PackageJourney::showStatus() const {
    std::cout << "Package status: " << this->status() << std::endl;

    if (this->package != NULL) {
        std::cout << "Delivery time remaining: "
                  << this->package->getDeliveryTime() << " days" << std::endl;
        this->package->Operation();
    }
}

//returns true if the package is suppossed to be delivered today
bool PackageJourney::isDeliveryDue() const {
    return this->package != NULL && this->package->getDeliveryTime() <= 0;
}

//returns the package being tracked by this journey
ShippingComponent* PackageJourney::getPackage() const {
    return this->package;
}
