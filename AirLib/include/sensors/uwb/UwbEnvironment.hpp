
#ifndef msr_airlib_UwbEnviroment_hpp
#define msr_airlib_UwbEnviroment_hpp

#include "common/AirSimSettings.hpp"
#include "sensors/SensorEnvironmentBase.hpp"
#include "physics/Kinematics.hpp"
#include "sensors/uwb/UwbBase.hpp"

// UwbSensoEnvironment: control multiple access

namespace msr { namespace airlib {
    class UwbEnvironment: public SensorEnvironmentBase{
    public:
        uint getUwbPairId(uint my_id){
            
        }

        virtual bool insertItem(const AirSimSettings::UwbTag* uwb_tag, const Kinematics * kinematic){
            if( uwb_tag->tag == FAKE_UWB_TAG){
                throw std::invalid_argument("Cannot insert fake tag\n");
            }
            auto it = tag_uwb_.find(uwb_tag->tag);
            if(it !=tag_uwb_.end() ){
                throw std::invalid_argument("Tag id should be unique\n");
                return false;
            }
            else{
                tag_kinematics_.insert(std::map<uint,const Kinematics*>::value_type(uwb_tag->tag, kinematic));
                tag_uwb_.insert(std::map<uint,const AirSimSettings::UwbTag*>::value_type(uwb_tag->tag,uwb_tag));
            }
            return true;
        }

        virtual const Pose&  getObjectPoseByID(uint tag){
            auto it  = tag_kinematics_.find(tag);
            if(it != tag_kinematics_.end()){
                const Kinematics* kinematic = it->second;
                return kinematic->getPose();
            }
            else{
                throw std::exception("Given tag does not exist");
            }
        }

        virtual const Pose& getPosById(uint tag) const {
            auto it  = tag_uwb_base_.find(tag);
            if(it != tag_uwb_base_.end()){
                const UwbBase* u   = it->second;
                return u->getPosition();
            }
            else{
                throw std::exception("Given tag does not exist");
            }
        }

        virtual uint chooseTag(uint mytag) const{
            // Here you can design a centralized algorithm for link assignment
            if (tagnum>1){
                int first,second;
                Choose2(tagnum, first, second);
                auto tag1 = params_.available_tags[first].tag;
                if(tag1 != params_.tag ){
                    return tag1;
                }
                else
                {
                    return( params_.available_tags[second].tag );
                }
            }
            else{
                return FAKE_UWB_TAG;
            }
        }

    
    private:
        std::map<uint, const Kinematics*> tag_kinematics_;
        std::map<uint, const AirSimSettings::UwbTag *> tag_uwb_;
        std::map<uint, const UwbBase *> tag_uwb_base_;
    };

}}

#endif