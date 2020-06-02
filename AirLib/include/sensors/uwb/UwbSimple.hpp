// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#ifndef msr_airlib_Uwb_hpp
#define msr_airlib_Uwb_hpp

#include <random>
#include "common/Common.hpp"
#include "UwbSimpleParams.hpp"
#include "UwbBase.hpp"
#include "common/GaussianMarkov.hpp"
#include "common/DelayLine.hpp"
#include "common/FrequencyLimiter.hpp"
#include "common/AirSimSettings.hpp"

namespace msr { namespace airlib {

class UwbSimple  : public UwbBase {
public:
    UwbSimple(const AirSimSettings::UwbSetting& setting = AirSimSettings::UwbSetting())
        : UwbBase(setting.sensor_name)
    {
        // initialize params, including tag
        params_.initializeFromSettings(setting);

        uncorrelated_noise_ = RandomGeneratorGausianR(0.0f, params_.unnorrelated_noise_sigma);
        //correlated_noise_.initialize(params_.correlated_noise_tau, params_.correlated_noise_sigma, 0.0f);


        //initialize frequency limiter
        freq_limiter_.initialize(params_.update_frequency, params_.startup_delay);
        delay_line_.initialize(params_.update_latency);
    }

    virtual void initializeWorldUwbInfo(std::vector<AirSimSettings::UwbTag>* uwb_tags ) = 0; // TODO: I want just use available_tags_ to point this object, is that right?

    //*** Start: UpdatableState implementation ***//
    virtual void resetImplementation() override
    {
        //correlated_noise_.reset();
        uncorrelated_noise_.reset();

        freq_limiter_.reset();
        delay_line_.reset();

        delay_line_.push_back(getOutputInternal());
    }

    virtual void update() override
    {
        UwbBase::update();

        freq_limiter_.update();

        if (freq_limiter_.isWaitComplete()) {
            delay_line_.push_back(getOutputInternal());
        }

        delay_line_.update();

        if (freq_limiter_.isWaitComplete())
            setOutput(delay_line_.getOutput());
    }
    //*** End: UpdatableState implementation ***//

    virtual ~UwbSimple() = default;

public: //types and variables
    std::vector<AirSimSettings::UwbTag>*  available_tags_; //TODO: add some code for initialization

protected:
    virtual real_T getRayLength(const Pose& pose, const uint tag ) = 0;
    const UwbSimpleParams& getParams()
    {
        return params_;
    }
    const uint getTag()
    {
        return params_.tag;
    }
private: //methods
    Output getOutputInternal()
    {
        Output output;
        const GroundTruth& ground_truth = getGroundTruth();

        //order of Pose addition is important here because it also adds quaternions which is not commutative!
        // TODO: in order to compile, the current tag is alway 1
        auto distance = getRayLength(params_.relative_pose + ground_truth.kinematics->pose,1);

        //add noise in distance (about 0.2m sigma)
        distance += uncorrelated_noise_.next();

        output.distance = distance;
        output.min_distance = params_.min_distance;
        output.max_distance = params_.max_distance;
        output.relative_pose = params_.relative_pose;
        output.time_stamp = clock()->nowNanos();

        return output;
    }

private:
    UwbSimpleParams params_;

    //GaussianMarkov correlated_noise_;
    RandomGeneratorGausianR uncorrelated_noise_;

    FrequencyLimiter freq_limiter_;
    DelayLine<Output> delay_line_;

    //start time
};

}} //namespace
#endif
