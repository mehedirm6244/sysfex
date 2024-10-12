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

#include "modules/swap.hpp"

#include <fstream>
#include <sstream>

std::string swap() {
  std::ifstream meminfo("/proc/meminfo");
  std::ostringstream output;

  if (!meminfo) {
    output << "Unknown";
    return output.str();
  }

  int free_swap_kb = 0;
  int total_swap_kb = 0;
  std::string key;

  while (meminfo >> key) {
    if (key == "SwapTotal:") {
      meminfo >> total_swap_kb;
    } else if (key == "SwapFree:") {
      meminfo >> free_swap_kb;
    }

    if (free_swap_kb and total_swap_kb) {
      break;
    }
  }
  
  if (!total_swap_kb) {
    output << "Unknown"; // Avoid division by zero
    return output.str();
  }

  int used_swap_kb = total_swap_kb - free_swap_kb;
  int used_swap_perc = (used_swap_kb * 100) / total_swap_kb;

  output << used_swap_kb / 1024 << "MiB used" << " (" << used_swap_perc << "%)";
  
  return output.str();
}
