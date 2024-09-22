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

#pragma once

#include <filesystem>
#include <vector>
#include <string>
#include <utility>

namespace sfImage {

  bool is_supported_image(const std::filesystem::path& image_path);

  std::pair<int, int> get_img_resolution(const std::filesystem::path& image_path);

  size_t img_height_when_width(const std::filesystem::path& image_path, size_t width);

  void preview_image(const std::filesystem::path& image_path, size_t width);

}
