#ifndef DELAYED_H
#define DELAYED_H

#include "PackageState.h"

class Delayed : public PackageState { //concreteState
    public:
        std::string name() const override;
        void resume(PackageJourney& journey) override;
        void deliver(PackageJourney& journey) override;
};

//Note delay can only resume and deliver

#endif
