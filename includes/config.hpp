#pragma once

#include <unordered_map>
#include <string>

class Config {
  const std::string default_config = R"(# Comments start with '#'

# Gap between ASCII/image and information
gap = 5

# Path to ASCII
# This path may point to an image as well
# `viu` is required for this feature to work
# Supported formats: '.png', '.jpg', '.jpeg', '.bmp', '.webp'
ascii = <path-to-ascii>

# For if ASCII is image
# The number of cells occupied by the image in X axis
image_width = 36

# Print text beside ASCII
# If disabled, information will be printed below the ASCII
info_beside_ascii = 1

# Clear screen before executing Sysfex
clear_screen = 0
)";

  std::unordered_map<std::string, std::string> config;

  void set_defaults() {
    config = {
      {"ascii",               ""   },
      {"clear_screen",        "0"  },
      {"gap",                 "5"  },
      {"image_width",         "36" },
      {"info_beside_ascii",   "1"  }
    };
  }

public:
  Config() {
    set_defaults();
  }

  static Config *the();

  void init(const std::string& dir);

  void set_property(const std::string& key, const std::string& value);

  void generate_config_file(const std::string& path);

  std::string get_property(const std::string& key);

};
