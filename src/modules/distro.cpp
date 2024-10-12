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

#include "modules/distro.hpp"

#include <fstream>
#include <string_view>

std::string distro() {
  std::ifstream osrelease_file("/etc/os-release");
  if (!osrelease_file) {
    return "Unknown";
  }

  std::string line;
  constexpr std::string_view pretty_name_prefix = "PRETTY_NAME=\"";

  while (std::getline(osrelease_file, line)) {
    if (line.find(pretty_name_prefix) != std::string::npos) {
      break;
    }
  }

  if (line.empty()) {
    return "Unknown";
  }

  /* Remove "PRETTY_NAME" from line */
  line = line.substr(pretty_name_prefix.length(), line.length() - (pretty_name_prefix.length() + 1));
  return line;
}
