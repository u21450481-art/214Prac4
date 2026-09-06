#include "NotDelivered.h"

#include "OnRoute.h"
#include "PackageJourney.h"

std::string NotDelivered::name() const {
    return "NotDelivered";
}

void NotDelivered::dispatch(PackageJourney& journey) {
    journey.changeState(new OnRoute());
}
