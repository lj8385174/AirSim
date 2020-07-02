#ifndef msr_airlib_SensorEnvironmentBase_hpp
#define msr_airlib_SensorEnvironmentBase_hpp

// Sensor Environment for UWB
#include "common/Common.hpp"


namespace msr { namespace airlib {
        class SensorEnvironmentBase{
            public:
                virtual const Pose&  getObjectPoseByID(uint object_id) =  0;
        };

}}

#endif