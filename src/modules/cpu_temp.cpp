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

#include "modules/cpu_temp.hpp"

std::string cpu_temp() {
  const std::filesystem::path temp_file_path = "/sys/class/thermal/thermal_zone0/temp";
  std::ifstream cpu_temp_file(temp_file_path);
  if (!cpu_temp_file) {
    return "Unavailable";
  }

  float temp;
  cpu_temp_file >> temp;
  temp /= 1000.0;
  
  std::ostringstream output;
  output << std::fixed << std::setprecision(2) << temp << "°C";
  return output.str();
}
