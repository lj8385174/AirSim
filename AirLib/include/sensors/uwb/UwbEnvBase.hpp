
#ifndef msr_airlib_UwbEnviroment_hpp
#define msr_airlib_UwbEnviroment_hpp

#include "common/AirSimSettings.hpp"
#include "sensors/SensorEnvBase.hpp"
#include "physics/Kinematics.hpp"
#include "sensors/uwb/UwbBase.hpp"

// UwbEnvBase: control multiple access

namespace msr { namespace airlib {
    class UwbEnvBase: public SensorEnvBase{
    public:
        // Initialization
        bool insertItem(const AirSimSettings::UwbTag* uwb_tag, const UwbBase* uwb_base){
            if( uwb_tag->tag == FAKE_UWB_TAG){
                throw std::invalid_argument("Cannot insert fake tag\n");
            }
            if( tagExist(uwb_tag->tag) ){
                throw std::invalid_argument("Tag id should be unique\n");
                return false;
            }
            else{
                // here we don't explicitly assign kinematic point of a static node to nullptr
                tag_uwb_settings_.insert(std::map<uint,const AirSimSettings::UwbTag*>::value_type(uwb_tag->tag,uwb_tag));
                tag_uwb_base_.insert(std::map<uint,const UwbBase*>::value_type(uwb_tag->tag, uwb_base));
                tag_is_static_.insert(std::map<uint,bool>::value_type(uwb_tag->tag, uwb_tag->is_static));
            }
            return true;
        }

        bool insertItem(const AirSimSettings::UwbSetting& setting, const UwbBase* uwb_base){
            
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

    protected:
        bool tagExist(uint tag){
            auto it = tag_uwb_base_.find(tag);
            if( it !=tag_uwb_base_.end() ){
                return true;
            }
            return false;
        }
    
    private:
        std::map<uint, const Kinematics*> tag_kinematics_;
        std::map<uint, const AirSimSettings::UwbTag *> tag_uwb_settings_;
        std::map<uint, const UwbBase *> tag_uwb_base_;
        std::map<uint, bool> tag_is_static_;
    };

}}

#endif