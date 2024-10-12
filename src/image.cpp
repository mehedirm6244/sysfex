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

#include "image.hpp"
#include "utils.hpp"

#include <utility>
#include <array>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

size_t sfImage::img_height_when_width(const std::filesystem::path& image_path, const size_t fixed_width) {
  int width = 0, height = 0, channels;
  unsigned char *data = stbi_load(image_path.c_str(), &width, &height, &channels, 0);

  stbi_image_free(data);

  return (width > 0) ? (fixed_width * height) / (width * 2) : 0;
}

void sfImage::preview_image(const std::filesystem::path& image_path, const size_t width) {
  /* Check if `viu` is installed in the system */
  if (sfUtils::taur_exec({ "sh", "-c", "command -v viu > /dev/null 2>&1" })) {
    sfUtils::taur_exec({"viu", image_path.string(), "-w", std::to_string(width)});
  }

  return;
}
