#include <string>
#include <sstream>
#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds[[maybe_unused]]) { 
    int hour = seconds/3600;
    seconds = seconds - (hour *3600);
    int min = seconds/60;
    seconds = seconds - (min*60);
    string hr,min,sec;
    std::stringstream hh;
    hh << hour;
    hh >> hr;

    std::stringstream mm;
    mm << min;
    mm >> min;

    std::stringstream ss;
    ss << seconds;
    ss >> sec;

    string time = hr + ":" +min + ":" + sec;

    return time; }