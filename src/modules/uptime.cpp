/**********************************************/
/* This file is a part of Sysfex              */
/* This function returns the uptime of the PC */
/**********************************************/

#include <cmath>
#include <fstream>
#include "uptime.hpp"

std::string uptime() {
    std::string time;
    double uptime;

    std::ifstream infile;
    infile.open("/proc/uptime");
    if (!infile.is_open())
        return "";

    /*
      /proc/uptime holds two numbers
      The first one is the total number of seconds the system has been up.
      The second one is how much of that time the machine has spent idle
      We want to deal with the first number only
    */
    infile >> uptime;
    infile.close();

    int days, hours, mins, secs;
    days = floor(uptime / 86400),
    hours = floor((uptime - days * 86400) / 3600),
    mins = floor((uptime - days * 86400 - hours * 3600) / 60),
    secs = uptime - (days * 86400) - (hours * 3600) - (mins * 60);

    if (days) {
        if (days <= 9) {
            time += "0";
        }
        time = time + std::to_string(days) + "d";
        if (days > 1) {
            time += "ays";
        }
        time += " ";
    }

    if (hours) {
        if (hours <= 9) {
            time += "0";
        }
        time = time + std::to_string(hours) + "h";
        if (hours > 1) {
            time += "rs";
        }
        time += " ";
    }

    if (mins) {
        if (mins <= 9) {
            time += "0";
        }
        time = time + std::to_string(mins) + "min";
        if (mins > 1) {
            time += "s";
        }
        time += " ";
    }

    if (secs) {
        if (secs <= 9) {
            time += "0";
        }
        time = time + std::to_string(secs) + "sec";
        if (secs > 1) {
            time += "s";
        }
    }

    return time;
}