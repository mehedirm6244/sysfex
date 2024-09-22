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

#include "modules/resolution.hpp"

std::string resolution() {
  std::string output;

  for (const auto& entry : std::filesystem::directory_iterator("/sys/class/drm")) {
    if (entry.is_directory()) {
      std::filesystem::path modes_path = entry.path() / "modes";
      if (std::filesystem::exists(modes_path)) {
        std::ifstream modes_file(modes_path);
        if (modes_file.is_open()) {
          std::string line;
          if (getline(modes_file, line)) {
            std::string single_resolution = line.substr(0, line.find(' '));
            output += single_resolution;
          }
          modes_file.close();
        }
      }
    }
  }

  output.erase(output.begin(), std::find_if(output.begin(), output.end(), [](unsigned char ch) {
    return !std::isspace(ch);
  }));

  return (output.empty()) ? "Unknown" : output;
}
