#include "OnRoute.h"

#include "Delayed.h"
#include "Delivered.h"
#include "PackageJourney.h"

std::string OnRoute::name() const {
    return "OnRoute";
}

void OnRoute::delay(PackageJourney& journey) {
    journey.changeState(new Delayed());
}

void OnRoute::deliver(PackageJourney& journey) {
    journey.changeState(new Delivered());
}

void OnRoute::checkDeliveryTime(PackageJourney& journey)
{
    if (journey.isDeliveryDue()) {
        journey.changeState(new Delivered());
    }
}
