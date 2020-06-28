// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "common/Common.hpp"
#include "GameFramework/Actor.h"
#include "sensors/uwb/UwbSimple.hpp"
#include "NedTransform.h"
#include "UnrealUwbEnvironment.h"

class UnrealUwbSensor : public msr::airlib::UwbSimple {
public:
    typedef msr::airlib::AirSimSettings AirSimSettings;

public:
    UnrealUwbSensor(const AirSimSettings::UwbSetting& setting,
        AActor* actor, const NedTransform* ned_transform);
    virtual void initializeWorldUwbInfo(std::vector<AirSimSettings::UwbTag>* uwb_tags );    
protected:
    virtual msr::airlib::real_T getRayLength(const msr::airlib::Pose& pose, const msr::airlib::uint tag) override;

private:
    using Vector3r = msr::airlib::Vector3r;
    using VectorMath = msr::airlib::VectorMath;


private:
    AActor* actor_;
    const NedTransform* ned_transform_;
};