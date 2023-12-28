#pragma once

#include <string>
#include <utility>

bool isAnImage(const std::string imagePath);

std::pair<int, int> getImageResolution(const char *imagePath);

int heightIfWidth(const std::string imagePath, int width);

void renderImage(const std::string imagePath, int width);