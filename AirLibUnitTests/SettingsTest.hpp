#ifndef msr_AirLibUnitTests_SettingsTest_hpp
#define msr_AirLibUnitTests_SettingsTest_hpp

#include "TestBase.hpp"
#include "common/Settings.hpp"
#include "common/AirSimSettings.hpp"

namespace msr { namespace airlib {

std::string getSimmodeName(const std::string& a){
    return a;
}

class SettingsTest : public TestBase {
public:
    virtual void run() override
    {   
        Settings& settings = Settings::loadJSonFile("D:\\projects\\AirSim\\AirLibUnitTests\\build\\x64\\Release\\settings.json");
        std::map<std::string, std::unique_ptr<AirSimSettings::VehicleSetting>> vehicles;
        printName("SettingsTest");
        
        AirSimSettings::singleton().load(std::bind(getSimmodeName,std::string("Car")));
        std::cout << "vehicle name"<< AirSimSettings::singleton().vehicles["Drone1"]->vehicle_name << std::endl;

        // AirSimSettings::

        std::cout << "sensor name:"<< AirSimSettings::singleton().vehicles["Drone1"]->sensors["UwbSensorWhatever"]->sensor_name << std::endl;

        AirSimSettings::UwbSetting&  uwb1 = * static_cast<AirSimSettings::UwbSetting*>(AirSimSettings::singleton().vehicles["Drone1"]->sensors["UwbSensorWhatever"].get());
        std::cout << "sensor tag:" << uwb1.tag << std::endl;
        //unused(uwb1);
        unused(settings);
    }
};


}}
#endif