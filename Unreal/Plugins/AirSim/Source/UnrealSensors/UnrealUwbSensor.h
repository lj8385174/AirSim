// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "common/Common.hpp"
#include "GameFramework/Actor.h"
#include "sensors/uwb/UwbSimple.hpp"
#include "NedTransform.h"
#include "UnrealUwbEnv.h"

class UnrealUwbSensor : public msr::airlib::UwbSimple {
public:
    typedef msr::airlib::AirSimSettings AirSimSettings;
    typedef msr::airlib::SensorEnvBase SensorEnvBase;

public:
    UnrealUwbSensor(const AirSimSettings::UwbSetting& setting,
        AActor* actor, const NedTransform* ned_transform, const std::shared_ptr<UnrealUwbEnv> sensor_env);

protected:
    virtual msr::airlib::real_T getRayLength(const msr::airlib::Pose& pose, const msr::airlib::uint tag) override;

private:
    using Vector3r = msr::airlib::Vector3r;
    using VectorMath = msr::airlib::VectorMath;


private:
    AActor* actor_;
    const NedTransform* ned_transform_;
};