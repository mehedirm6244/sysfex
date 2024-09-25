/*

This file is from Sysfex, another system info fetching tool

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#include "modules/uptime.hpp"

std::string uptime() {
  std::ifstream infile("/proc/uptime");
  if (!infile.is_open()) {
    return "Unknown";
  }

  double uptime;
  infile >> uptime;
  infile.close();

  int days = static_cast<int>(uptime / 86400);
  int hours = static_cast<int>((uptime - days * 86400) / 3600);
  int mins = static_cast<int>((uptime - days * 86400 - hours * 3600) / 60);
  int secs = static_cast<int>(uptime - days * 86400 - hours * 3600 - mins * 60);

  std::string output;

  if (days) {
    output += std::to_string(days) + "day" + (days > 1 ? "s " : " ");
  }

  if (hours) {
    output += std::to_string(hours) + "hour" + (hours > 1 ? "s " : " ");
  }

  if (mins) {
    output += std::to_string(mins) + "min" + (mins > 1 ? "s " : " ");
  }

  if (secs) {
    output += std::to_string(secs) + "sec" + (secs > 1 ? "s" : "");
  }

  return output;
}
