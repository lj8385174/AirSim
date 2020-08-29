#include "UnrealUwbEnv.h"
#include <stdexcept>

// SensorEnvBase& UnrealUwbEnv::singleton{
//     // static SensorEnvBase&  instance = 
// }
// msr::airlib::SensorEnvBase::PoseSimple  UnrealUwbEnv::getObjectPoseByID(uint tag){
//     PoseSimple pose;
//     auto it  = tag_actor_.find(tag);
//     if(it != tag_actor_.end()){
//         const AActor& actor = it->second;
        
//     }
//     else{
//         throw std::exception("Given tag does not exist");
//     }
// };


 void UnrealUwbEnv::insertItemActor(const AirSimSettings::UwbTag& uwb_tag, const AActor* actor){
      if( uwb_tag.tag == FAKE_UWB_TAG){
            throw std::invalid_argument("Cannot insert fake tag\n");
        }
        auto it = tag_actor_.find(uwb_tag.tag);
        if(it !=tag_actor_.end() ){
            throw std::invalid_argument("Tag id should be unique\n");
            return false
        }
        else{
            tag_actor_.insert(std::map<uint,const AActor*>::value_type(uwb_tag.tag, actor);
            if(actors_::find(vec.begin(), actors_.end(), item) != actors_.end() ){
                actors_.push_back(actor);
            }
        }
        return true;
 };

