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

#include <fstream>
#include <sstream>

std::string ram() {
  std::ifstream meminfo("/proc/meminfo");
  std::ostringstream output;

  if (!meminfo) {
    output << "Unknown";
    return output.str();
  }

  int free_mem_kb = 0;
  int total_mem_kb = 0;
  std::string key;

  while (meminfo >> key) {
    if (key == "MemTotal:") {
      meminfo >> total_mem_kb;
    } else if (key == "MemAvailable:") {
      meminfo >> free_mem_kb;
    }

    if (free_mem_kb and total_mem_kb) {
      break;
    }
  }

  if (!total_mem_kb) {
    output << "Unknown"; // Avoid division by zero
    return output.str();
  }

  int used_mem_kb = total_mem_kb - free_mem_kb;
  int used_mem_perc = (used_mem_kb * 100) / total_mem_kb;

  output << used_mem_kb / 1024 << "MiB used " << "(" << used_mem_perc << "%)";
  return output.str();
}
