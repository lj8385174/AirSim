#ifndef msr_airlib_SensorEnvBase_hpp
#define msr_airlib_SensorEnvBase_hpp

// Sensor Environment for UWB
#include "common/Common.hpp"


namespace msr { namespace airlib {
        class SensorEnvBase{
            public:
                virtual const Pose&  getObjectPoseByID(uint object_id) =  0;
        };

}}

#endif