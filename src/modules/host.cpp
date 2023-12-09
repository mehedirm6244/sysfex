/****************************************************/
/* This file is a part of Sysfex                    */
/* This function returns the host name set by admin */
/****************************************************/

#include <fstream>
#include "host.hpp"

std::string host() {
    std::string host;
    std::ifstream infile;
    infile.open("/proc/sys/kernel/hostname");
    if (!infile.is_open()) {
        return "";
    }
    infile >> host;
    infile.close();

    return host;
}