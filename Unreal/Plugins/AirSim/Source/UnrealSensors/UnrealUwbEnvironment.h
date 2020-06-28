#pragma once

#include "common/Common.hpp"
#include "GameFramework/Actor.h"
#include "sensors/uwb/UwbSimple.hpp"
#include "sensors/uwb/UwbEnvironment.hpp"
#include "NedTransform.h"


class UnrealUwbEnvironment: public msr::airlib::UwbEnvironment{
public:       
        typedef msr::airlib::AirSimSettings AirSimSettings;
        typedef msr::airlib::uint uint;
        void insertItemActor(const AirSimSettings::UwbTag& uwb_tag, const AActor* actor);
        // std::vector<const AActor*>
// private:
        std::map<uint, const AActor*> tag_actor_;
        std::vector<const AActor*> actors_;
};