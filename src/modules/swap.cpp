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

std::string swap() {
  int free_swap = 0;
  int total_swap = 0;
  int used_swap;
  int used_swap_perc;

  std::ifstream meminfo("/proc/meminfo");
  if (!meminfo.is_open()) {
    return "Unknown";
  }

  std::string key;
  while (meminfo >> key) {
    if (key == "SwapTotal:") {
      meminfo >> total_swap;
    } else if (key == "SwapFree:") {
      meminfo >> free_swap;
    }

    if (free_swap and total_swap) {
      break;
    }
  }
  meminfo.close();

  used_swap = total_swap - free_swap;
  used_swap_perc = (used_swap * 100) / total_swap;

  std::ostringstream output;

  output << std::to_string((used_swap) / 1024) << "MiB used " << "(" << std::to_string(used_swap_perc) << "%)";
  return output.str();
}
