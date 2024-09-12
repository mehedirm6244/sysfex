#include <fstream>

#include <modules/host.hpp>

std::string host() {
  std::ifstream infile("/proc/sys/kernel/hostname");

  if (!infile.is_open()) {
    return "Unknown";
  }

  std::string output;
  infile >> output;
  infile.close();

  return output;
}
