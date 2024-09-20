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

std::string gpu() {
  /* I'm sorry */
  std::string raw_command = R"(lspci -mm |
    awk -F '\"|\" \"|\\(' \
      '/"Display|"3D|"VGA/ {
        a[$0] = $1 " " $3 " " ($(NF-1) ~ /^$|^Device [[:xdigit:]]+$/ ? $4 : $(NF-1))
      }
      END { for (i in a) {
        if (!seen[a[i]]++) {
          sub("^[^ ]+ ", "", a[i]);
          print a[i]
        }
      }
    }
  ')";

  std::string output = sfUtils::get_output_of(raw_command.c_str());

  /*Remove unnecessary patterns from output */
  std::vector<std::string> removables = {
    "Integrated Graphics Controller", "Corporation"
  };

  for (auto removable : removables) {
    size_t pos = output.find(removable);
    if (pos != std::string::npos) {
      output.erase(pos, removable.length());
    }
  }

  /* Remove leading, trailing and extra spaces from output */
  output = sfUtils::trim_string_spaces(output);

  return output;
}
