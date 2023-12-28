#include <filesystem>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <image.hpp>


bool isAnImage(const std::string imagePath) {
  std::string extension = std::filesystem::path(imagePath).extension();
  std::vector<std::string> supportedExtensions = {
    ".bmp",
    ".png",
    ".jpg",
    ".jpeg",
    ".webp"
  };

  for (auto currentExtension: supportedExtensions) {
    if (currentExtension == extension) {
      return true;
    }
  }
  return false;
}

std::pair<int, int> getImageResolution(const char *imagePath) {
  int x, y;
  stbi_load(imagePath, &x, &y, 0, 0);
  return { x, y };
}

int heightIfWidth(std::string imagePath, const int width) {
  std::pair<int, int> res = getImageResolution(imagePath.c_str());
  int height = ((width * res.second) / (res.first * 2));
  return height;
}

void renderImage(std::string imagePath, int width) {
  /* If "viu" is not installed, do nothing */
  

  std::string cmd = "viu " + imagePath + " -w " + std::to_string(width);
  system(cmd.c_str());
}