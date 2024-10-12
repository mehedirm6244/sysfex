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

#include "modules/model.hpp"

#include <fstream>
#include <sstream>

std::string model() {
  std::ifstream product_name_file("/sys/devices/virtual/dmi/id/product_name");
  std::ifstream product_version_file("/sys/devices/virtual/dmi/id/product_version");
  std::stringstream model_info;

  if (product_name_file) {
    std::string product_name;
    std::getline(product_name_file, product_name);
    model_info << product_name;
  } else {
    model_info << "Unknown";
  }

  if (product_version_file) {
    std::string product_version;
    std::getline(product_version_file, product_version);
    model_info << " " << product_version;
  }

  return model_info.str();
}
