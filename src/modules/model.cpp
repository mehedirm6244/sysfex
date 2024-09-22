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

std::string model() {
  std::ifstream product_name("/sys/devices/virtual/dmi/id/product_name");
  if (!product_name.is_open()) {
    return "Unknown";
  }

  std::string model_name;
  getline(product_name, model_name);
  product_name.close();

  std::ifstream product_version("/sys/devices/virtual/dmi/id/product_version");
  if (!product_version.is_open()) {
    return "";
  }

  std::string model_version;
  getline(product_version, model_version);
  product_version.close();

  std::string output = model_name + " " + model_version;
  return output;
}
