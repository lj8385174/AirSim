// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "UnrealUwbSensor.h"
#include "AirBlueprintLib.h"
#include "common/Common.hpp"
#include "NedTransform.h"

UnrealUwbSensor::UnrealUwbSensor(const AirSimSettings::UwbSetting& setting,
    AActor* actor, const NedTransform* ned_transform,const std::shared_ptr<UnrealUwbEnv> sensor_env)
    : msr::airlib::UwbSimple(setting, sensor_env), actor_(actor), ned_transform_(ned_transform), 
{
}


msr::airlib::real_T UnrealUwbSensor::getRayLength(const msr::airlib::Pose& pose, const msr::airlib::uint tag)
{
    //update ray tracing
    Vector3r start = pose.position;
    auto max_dis1  = getParams().max_distance;
    auto min_dis1  = getParams().min_distance;
    auto max_dis2  = uwb_env_ -> tag_uwb_[tag]->max_distance;
    auto min_dis2  = uwb_env_ -> tag_uwb_[tag]->min_distance;
    if(uwb_env_->tag_uwb_[tag]->is_static){
        Vector3r end   =  uwb_env_ -> tag_uwb_[tag]->pose.position;
        auto distance  = (start - end).norm();
        auto max_dis  = min(max_dis1,max_dis2);
        auto min_dis  = max(min_dis1,min_dis2);
        if (distance>max_dis || distance<min_dis ){
            // not reachable 
            return NOT_REACHABLE_DISTANCE_RESULT;
        }
        else{
            FHitResult dist_hit = FHitResult(ForceInit);
            // AActor* except_actor   = (UnrealUwbEnv*)uwb_env_ -> tag_actor_[tag];
            bool is_hit = UAirBlueprintLib::GetObstacle(actor_, ned_transform_->fromLocalNed(start), ned_transform_->fromLocalNed(end), dist_hit );
            float dist = is_hit? NOT_REACHABLE_DISTANCE_RESULT: distance / 100.0f;
            return dist;
        }
    }
    else{
        Vector3r end   = uwb_env_->tag_kinematics_[tag].getPose().position + wb_env_ -> tag_uwb_[tag]->pose.position;
        auto distance  = (start - end).norm();
        auto max_dis  = min(max_dis1,max_dis2);
        auto min_dis  = max(min_dis1,min_dis2);
        if (distance>max_dis || distance<min_dis ){
            // not reachable 
            return NOT_REACHABLE_DISTANCE_RESULT;
        }
        else{
            FHitResult dist_hit = FHitResult(ForceInit);
            AActor* except_actor   = (UnrealUwbEnv*)uwb_env_ -> tag_actor_[tag]; //TODO: current it merely ignore from-to actors, while other vehicles should be included.
            bool is_hit = UAirBlueprintLib::GetObstacle(actor_, ned_transform_->fromLocalNed(start), ned_transform_->fromLocalNed(end), dist_hit, except_actor );
            float dist = is_hit? NOT_REACHABLE_DISTANCE_RESULT: distance / 100.0f;
            return dist;
        }
    }
}
