#include <sstream>
#include <fstream>

#include <modules/uptime.hpp>

std::string uptime() {
  std::ifstream infile("/proc/uptime");
  if (!infile.is_open()) {
    return "";
  }

  double uptime;
  infile >> uptime;
  infile.close();

  int days = static_cast<int>(uptime / 86400);
  int hours = static_cast<int>((uptime - days * 86400) / 3600);
  int mins = static_cast<int>((uptime - days * 86400 - hours * 3600) / 60);
  int secs = static_cast<int>(uptime - days * 86400 - hours * 3600 - mins * 60);

  std::ostringstream output;

  /* Format output */
  if (days) {
    output << days << "day" << (days > 1 ? "s " : " ");
  }

  if (hours) {
    output << hours << "hour" << (hours > 1 ? "s " : " ");
  }

  if (mins) {
    output << mins << "min" << (mins > 1 ? "s " : " ");
  }

  if (secs) {
    output << secs << "sec" << (secs > 1 ? "s" : "");
  }

  return output.str();
}
