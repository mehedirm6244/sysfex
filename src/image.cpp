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

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


bool sfImage::is_supported_image(const std::filesystem::path& image_path) {
  std::string extension = image_path.extension();
  std::vector<std::string> supported_extensions = {
    ".bmp", ".png", ".jpg", ".jpeg", ".webp"
  };

  for (auto supported_extension : supported_extensions) {
    if (extension == supported_extension) {
      return true;
    }
  }
  return false;
}

std::pair<int, int> sfImage::get_img_resolution(const std::filesystem::path& image_path) {
  int width, height, channels;
  unsigned char *data = stbi_load(image_path.c_str(), &width, &height, &channels, 0);

  if (!data) {
    return { 0, 0 };
  }

  stbi_image_free(data);
  return { width, height };
}

size_t sfImage::img_height_when_width(const std::filesystem::path& image_path, size_t width) {
  std::pair<int, int> res = get_img_resolution(image_path.c_str());
  if (res.first == 0) {
    return 0;
  }
  return (width * res.second) / (res.first * 2);
}

void sfImage::preview_image(const std::filesystem::path& image_path, size_t width) {
  /* Check if `viu` is installed in the system */
  if (std::system("command -v viu > /dev/null 2>&1")) {
    /* Nothing */
    return;
  }

  std::string cmd = "viu " + std::string(image_path) + " -w " + std::to_string(width);
  std::system(cmd.c_str());
}
