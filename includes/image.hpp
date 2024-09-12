#pragma once

#include <string>
#include <utility>

bool is_supported_image(const std::string& image_path);

std::pair<int, int> get_img_resolution(const char *image_path);

size_t img_height_when_width(const std::string& image_path, size_t width);

void preview_image(const std::string& image_path, size_t width);
