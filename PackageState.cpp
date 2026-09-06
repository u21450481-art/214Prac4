#include "PackageState.h"

#include <iostream>

PackageState::~PackageState() {
}

//Note the (void) journey prevents compiler warnings about operations not being used or implmented as not all states use all the transitions.

void PackageState::dispatch(PackageJourney& journey) {
    (void) journey;
    std::cout << "Error: package cannot be dispatched in its current state." << std::endl;
}

void PackageState::delay(PackageJourney& journey) {
    (void) journey;
    std::cout << "Error: package cannot be delayed in its current state." << std::endl;
}

void PackageState::resume(PackageJourney& journey) {
    (void) journey;
    std::cout << "Error: package cannot resume in its current state." << std::endl;
}

void PackageState::deliver(PackageJourney& journey) {
    (void) journey;
    std::cout << "Error: package cannot be delivered in its current state." << std::endl;
}

void PackageState::checkDeliveryTime(PackageJourney& journey) {
    (void) journey;
}

