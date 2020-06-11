
#ifndef msr_airlib_UwbEnviroment_hpp
#define msr_airlib_UwbEnviroment_hpp

#include "sensors/SensorEnvironmentBase.hpp"
#include "physics/Kinematics.hpp"

// UwbSensoEnvironment: control multiple access

namespace msr { namespace airlib {
    class UwbEnvironment: public SensorEnvironmentBase{
    public:
        // std::map<uint, const &> tag_actor_;
        // std::map<uint, AirSimSettings::UwbTag& > tag_uwb_;
        std::map<uint, const Kinematics*> tag_kinematics_;
        std::map<uint, const AirSimSettings::UwbTag *> tag_uwb_;

        uint getUwbPairId(uint my_id){
            
        }

        virtual bool  UnrealUwbEnvironment::insertItem(const AirSimSettings::UwbTag* uwb_tag, const Kinematics * kinematic){
            if( uwb_tag->tag == FAKE_UWB_TAG){
                throw std::invalid_argument("Cannot insert fake tag\n");
            }
            auto it = tag_uwb_.find(uwb_tag->tag);
            if(it !=tag_uwb_.end() ){
                throw std::invalid_argument("Tag id should be unique\n");
                return false
            }
            else{
                tag_kinematics_.insert(std::map<uint,const Kinematics*>::value_type(uwb_tag->tag, kinematic);
                tag_uwb_.insert(std::map<uint,const AirSimSettings::UwbTag*>::value_type(uwb_tag->tag,uwb_tag));
            }
            return true;
        }

        virtual const Pose&  UnrealUwbEnvironment::getObjectPoseByID(uint tag){
            auto it  = tag_kinematics_.find(tag);
            if(it != tag_kinematics_.end()){
                const Kinematics* kinematic = it->second;
                return kinematic->getPose();
            }
            else{
                throw std::exception("Given tag does not exist");
            }
        }

    // private:
        //get all available tags

    };

}}

#endif