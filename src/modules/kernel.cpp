/********************************************/
/* This file is a part of Sysfex            */
/* This function returns the kernel version */
/********************************************/

#include <fstream>
#include "../utils.hpp"
#include "kernel.hpp"

std::string kernel() {
  std::ifstream infile;
  infile.open("/proc/sys/kernel/osrelease");
  if (!infile.is_open()) {
    /*
      If no `osrelease` file exists the return the output of `uname -r`
      which outputs the kernel you're using
    */
    return getOutputOf(std::string("uname -r").c_str());
  }

  std::string output;
  infile >> output;
  return output;
}