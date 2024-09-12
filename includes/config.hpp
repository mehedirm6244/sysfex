#pragma once

#include <unordered_map>
#include <string>

class Config {
  std::unordered_map<std::string, std::string> config;

  void set_defaults() {
    config = {
      {"ascii",               "/opt/sysfex/ascii/tux.txt" },
      {"clear_screen",        "1"                         },
      {"gap",                 "10"                        },
      {"image_width",         "36"                        },
      {"info_beside_ascii",   "1"                         }
    };
  }

public:
  Config() {
    set_defaults();
  }

  static Config *the();

  void set_property(const std::string& key, const std::string& value);

  std::string get_property(const std::string& key);

  void init(const std::string& dir);
};
