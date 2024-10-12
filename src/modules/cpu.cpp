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

#include "modules/cpu.hpp"
#include "utils.hpp"

#include <array>
#include <algorithm>
#include <fstream>
#include <cctype> // for std::isspace
#include <string_view>

std::string cpu() {
  constexpr std::string_view model_name = "model name";
  std::ifstream cpu_info("/proc/cpuinfo");

  if (!cpu_info) {
    return "Unknown";
  }

  std::string output, current_line;
  while (std::getline(cpu_info, current_line)) {
    if (current_line.find(model_name) != std::string::npos) {
      output = current_line;
      break;
    }
  }

  if (output.empty()) {
    return "Unknown";
  }

  constexpr std::array<std::string_view, 14> removables = {
    "model name", "(TM)", "(tm)", "(R)", "(r)", "CPU", "(Processor)",
    "Technologies, Inc", "Core", "Dual-Core", "Quad-Core", "Six-Core", "Eight-Core"
  };

  /* Remove unnecessary patterns from output */
  for (const std::string_view removable : removables) {
    const size_t pos = output.find(removable);
    if (pos != std::string::npos) {
      output.erase(pos, removable.length());
    }
  }

  /* Trim leading whitespaces and colon */
  output.erase(output.begin(), std::find_if(output.begin(), output.end(), [](unsigned char ch) {
    return !std::isspace(ch) and ch != ':';
  }));

  /* Trim trailing and excess whitespaces */
  output = sfUtils::trim_string_spaces(output);

  return output;
}
