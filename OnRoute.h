#ifndef ONROUTE_H
#define ONROUTE_H

#include "PackageState.h"

class OnRoute : public PackageState { //concreteState

    public:
        std::string name() const override;
        void delay(PackageJourney& journey) override;
        void deliver(PackageJourney& journey) override;
        void checkDeliveryTime(PackageJourney& journey) override;
};

//note onRoute can only deliver or delay

#endif
