/****************************************/
/* This file is a part of Sysfex        */
/* This function returns used and total */
/* memory aka RAM                       */
/****************************************/

#include <fstream>
#include "ram.hpp"

std::string ram() {
    int freeMemory = 0, totalMemory = 0;

    std::ifstream infile;
    infile.open("/proc/meminfo");
    if (!infile.is_open()) /* Why wouldn't /proc/meminfo exist anyways? */
        return "";

    while (infile.good() and !(freeMemory and totalMemory)) { /* /proc/meminfo has a lot of stuff about memory in it
                                                               We have to look for the whole file until we get what we want */
        std::string currentKey;
        infile >> currentKey;

        if (currentKey == "MemTotal:")
            infile >> totalMemory;

        if (currentKey == "MemAvailable:")
            infile >> freeMemory;
    }
    infile.close();

    std::string ram = std::to_string((totalMemory - freeMemory) / 1024)
                      + "MiB /" + std::to_string(totalMemory / 1024) + "MiB";
    return ram;
}