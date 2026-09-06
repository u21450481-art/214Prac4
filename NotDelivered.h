#ifndef NOTDELIVERED_H
#define NOTDELIVERED_H

#include "PackageState.h"

class NotDelivered : public PackageState { //concreteState

    public:
        std::string name() const override;
        void dispatch(PackageJourney& journey) override;
};

#endif
