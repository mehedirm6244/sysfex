#include <filesystem>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

/* Sysfex headers */
#include <image.hpp>

bool is_supported_image(const std::string& image_path) {
  std::string extension = std::filesystem::path(image_path).extension();
  std::vector<std::string> supported_img_extensions = {
    ".bmp", ".png", ".jpg", ".jpeg", ".webp"
  };

  for (auto supported_extension: supported_img_extensions) {
    if (supported_extension == extension) {
      return true;
    }
  }
  return false;
}

std::pair<int, int> get_img_resolution(const char *image_path) {
  int width, height, channels;
  unsigned char *data = stbi_load(image_path, &width, &height, &channels, 0);

  if (!data) {
    return { 0, 0 };
  }

  stbi_image_free(data);
  return { width, height };
}

size_t img_height_when_width(const std::string& image_path, size_t width) {
  std::pair<int, int> res = get_img_resolution(image_path.c_str());
  if (res.first == 0) {
    return 0;
  }
  return (width * res.second) / (res.first * 2);
}

void preview_image(const std::string& image_path, size_t width) {
  /* Check if `viu` is installed in the system */
  if (std::system("command -v viu > /dev/null 2>&1")) {
    /* Nothing */
    return;
  }

  std::string cmd = "viu " + image_path + " -w " + std::to_string(width);
  std::system(cmd.c_str());
}
