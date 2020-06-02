// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#ifndef msr_airlib_UwbBase_hpp
#define msr_airlib_UwbBase_hpp


#include "sensors/SensorBase.hpp"


namespace msr { namespace airlib {

class UwbBase  : public SensorBase {
public:
    UwbBase(const std::string& sensor_name = "")
        : SensorBase(sensor_name)
    {
    }

public: //types
    struct Output { //same fields as ROS message
        TTimePoint time_stamp;
        uint   pair_tag;  //paired uwb node's tag
        real_T distance;    //meters
        real_T min_distance;//m
        real_T max_distance;//m
        Pose relative_pose;
    };


public:
    virtual void reportState(StateReporter& reporter) override
    {
        //call base
        UpdatableObject::reportState(reporter);

        reporter.writeValue("UWB Dist-Curr", output_.pair_tag);

        reporter.writeValue("UWB Dist-Curr", output_.distance);
    }

    const Output& getOutput() const
    {
        return output_;
    }

protected:
    void setOutput(const Output& output)
    {
        output_ = output;
    }


private:
    Output output_;
};


}} //namespace
#endif
