#ifndef msr_airlib_SensorEnvironmentBase_hpp
#define msr_airlib_SensorEnvironmentBase_hpp

// Sensor Environment for UWB
#include "common/Common.hpp"


namespace msr { namespace airlib {
        class SensorEnvironmentBase{
            public:
                virtual PoseSimple getObjectPoseByID(uint object_id) =  0;
                // virtual SensorEnvironmentBase& singleton() = 0;
        };

}}

#endif