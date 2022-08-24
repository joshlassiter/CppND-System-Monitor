#include <string>
#include <sstream>
#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int hour = seconds/3600;
    seconds = seconds - (hour *3600);
    int minute = seconds/60;
    seconds = seconds - (minute*60);
    string hr,min,sec;
    std::stringstream hh;
    hh << hour;
    hh >> hr;

    std::stringstream mm;
    mm << minute;
    mm >> min;

    std::stringstream ss;
    ss << seconds;
    ss >> sec;

    if (hour<10){
        hr = "0" + hr;
    }
    if (minute<10){
        min = "0" + min;
    }
    if (seconds<10){
        sec = "0" + sec;
    }
    string time = hr + ":" + min + ":" + sec;

    return time; }
