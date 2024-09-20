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

#include "modules/ram.hpp"

std::string ram() {
  int free_mem = 0;
  int total_mem = 0;
  int used_mem;
  int used_mem_perc;

  std::ifstream meminfo("/proc/meminfo");
  if (!meminfo.is_open()) {
    return "Unknown";
  }

  std::string key;
  while (meminfo >> key) {
    if (key == "MemTotal:") {
      meminfo >> total_mem;
    } else if (key == "MemAvailable:") {
      meminfo >> free_mem;
    }

    if (free_mem and total_mem) {
      break;
    }
  }
  meminfo.close();

  used_mem = total_mem - free_mem;
  used_mem_perc = (used_mem * 100) / total_mem;

  std::ostringstream output;

  output << std::to_string((used_mem) / 1024) << "MiB used " << "(" << std::to_string(used_mem_perc) << "%)";
  return output.str();
}
