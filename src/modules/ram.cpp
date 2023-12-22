/**************************************************************/
/* This file is a part of Sysfex                              */
/* This function returns used and total usable memory aka RAM */
/**************************************************************/

#include <fstream>
#include "ram.hpp"

std::string ram() {
  int freeMemory = 0, totalMemory = 0, usedMemory, usedPerc;

  std::ifstream infile;
  infile.open("/proc/meminfo");       /* /proc/meminfo has a lot of stuff about memory in it */
  if (!infile.is_open()) {            /* Why wouldn't that exist anyway? */
    return "";
  }

  /* We need to go through the whole /proc/meminfo until we get what we want */
  while (infile.good() and !(freeMemory and totalMemory)) {
    std::string currentKey;
    infile >> currentKey;

    if (currentKey == "MemTotal:") {
      infile >> totalMemory;
    }

    if (currentKey == "MemAvailable:") {
      infile >> freeMemory;
    }
  }
  infile.close();

  usedMemory = totalMemory - freeMemory;
  usedPerc = (usedMemory * 100) / totalMemory;

  std::string output = std::to_string((usedMemory) / 1024)
                       + "MiB of " + std::to_string(totalMemory / 1024) + "MiB "
                       + "(" + std::to_string(usedPerc) + "%)";
  return output;
}