/****************************************************/
/* This file is a part of Sysfex                    */
/* This function returns the host name set by admin */
/****************************************************/

#include <fstream>
#include <modules/host.hpp>

std::string host() {
  std::string output;
  std::ifstream infile;
  infile.open("/proc/sys/kernel/hostname");
  if (!infile.is_open()) {
    return "";
  }
  infile >> output;
  infile.close();

  return output;
}