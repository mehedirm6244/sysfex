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

#include "modules/gpu.hpp"
#include <array>

std::string gpu() {
  constexpr std::array<std::string_view, 2> removables = {
    "Integrated Graphics Controller", "Corporation"
  };

  std::stringstream cmd_output = std::stringstream(sfUtils::get_output_of("lspci -mm"));
  std::string line;

  std::vector<std::string> gpus;
  while (std::getline(cmd_output, line, '\n')) {
    if (line.find("\"Display") != std::string::npos
        or line.find("\"VGA") != std::string::npos or line.find("\"3D") != std::string::npos) {
      std::vector<std::string> pieces;
      std::regex rgx(R"("|" "|\()");
      std::sregex_token_iterator iter(line.begin(), line.end(), rgx, -1);
      std::sregex_token_iterator end;

      for (; iter != end; iter++) {
        if (*iter != " ") {
          pieces.push_back(*iter);
        }
      }

      std::string gpu;
      gpu += pieces[2];
      if (pieces[pieces.size() - 1].find("Device ")) {
        gpu += pieces[pieces.size() - 1];
      } else {
        gpu += pieces[3];
      }

      for (const auto& removable: removables) {
        const size_t pos = gpu.find(removable);
        if (pos != std::string::npos) {
          gpu.erase(pos, removable.length());
        }
      }

      gpus.push_back(gpu);
    }
  }

  if (gpus.size() > 1) {
    std::stringstream output;

    for (int i = 0; i < gpus.size(); i++) {
      output << "(" << i + 1 << ") " << gpus[i];

      if (i != gpus.size() - 1) {
        output << ", ";
      }
    }
    return output.str();
  } else {
    return gpus[0];
  }
}
