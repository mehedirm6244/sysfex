/********************************************/
/* This file is a part of Sysfex            */
/* This function returns the kernel version */
/********************************************/

#include <fstream>
#include "../functions.hpp"
#include "kernel.hpp"

std::string kernel() {
    std::ifstream infile;
    infile.open("/proc/sys/kernel/osrelease");
    if (!infile.is_open()) {
        return exec(std::string("uname -r").c_str()); /* If there is no osrelease file,
																								then return the output of `uname -r` */
    }

    std::string kernel;
    infile >> kernel;
    return kernel;
}