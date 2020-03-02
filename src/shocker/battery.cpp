#include <fstream>
#include <string>
#include <sstream>

#include <boost/algorithm/string/trim.hpp>

#include "shocker.hpp"

int current_level = -1; // -1 means never looked at

int shocker::battery::get_level() {
    if (current_level == -1) {
        std::ifstream battfile("/sys/class/power_supply/sony_controller_battery_f4:93:9f:99:10:90/capacity");
        std::stringstream battstream;
        battstream << battfile.rdbuf();
        battfile.close();

        std::string batt = battstream.str();
        boost::algorithm::trim(batt);
        int battint = std::stoi(batt);

        current_level = battint;
    }

    return current_level;
}


std::string shocker::battery::get_icon() {
    int battint = shocker::battery::get_level();
    std::string batt = std::to_string(battint);

    std::string str_batticon = "battery-";
    if (battint == 100) { str_batticon += "100"; }
    else {
        str_batticon += "0";
        str_batticon += batt.at(0); // percentage rounded down
        str_batticon += "0";
    }

    std::ifstream chargefile("/sys/class/power_supply/sony_controller_battery_f4:93:9f:99:10:90/status");
    std::stringstream chargestream;
    chargestream << chargefile.rdbuf();
    chargefile.close();

    std::string charge = chargestream.str();
    boost::algorithm::trim(charge);
    if (charge == "Charging") { str_batticon += "-charging"; }

    return str_batticon;
}
