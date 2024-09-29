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
#include <array>

std::string cpu() {
  constexpr std::string_view model_name = "model name";
  std::string output;

  std::ifstream cpu_info("/proc/cpuinfo");
  if (!cpu_info.is_open()) {
    return "Unknown";
  }

  while (cpu_info.good()) {
    std::string current_line;
    std::getline(cpu_info, current_line);

    if (current_line.find(model_name) != std::string::npos) {
      output = current_line;
      break;
    }
  }
  cpu_info.close();

  if (output.empty()) {
    return "Unknown";
  }

  /* Erase "model name" from output */
  output = output.substr(model_name.length());

  /*Remove unnecessary patterns from output */
  constexpr std::array<std::string_view, 13> removables = {
    "(TM)", "(tm)", "(R)", "(r)", "CPU", "(Processor)", "Technologies, Inc",
    "Core", "Dual-Core", "Quad-Core", "Six-Core", "Eight-Core"
  };

  for (const std::string_view removable : removables) {
    const size_t pos = output.find(removable);
    if (pos != std::string::npos) {
      output.erase(pos, removable.length());
    }
  }

  /* Trim leading spaces and colon */
  output.erase(output.begin(), std::find_if(output.begin(), output.end(), [](unsigned char ch) {
    return !std::isspace(ch) && ch != ':';
  }));

  /* Trim trailing and extra spaces */
  output = sfUtils::trim_string_spaces(output);

  return output;
}
