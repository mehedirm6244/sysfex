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

#include "config.hpp"
#include "utils.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>

Config sysfex_config;

Config *Config::the() {
  return &sysfex_config;
}

void Config::set_property(const std::string_view key, const std::string_view value) {
  if (config.find(key.data()) != config.end()) {
    config[key.data()] = value;
  }
}

std::string Config::get_property(const std::string_view key) {
  return (config.find(key.data()) != config.end()) ? config[key.data()] : "";
}

void Config::generate_config_file(const std::string_view path) {
  std::ofstream generated_file(path.data());
  generated_file << default_config;
  generated_file.close();
}

void Config::init(const std::string_view dir) {
  std::ifstream config_file(dir.data());
  if (!config_file) {
    return;
  }

  std::string current_line;
  while (std::getline(config_file, current_line)) {
    /*
      Remove all spaces from the current line
      Do not use sfUtils::trim_string_spaces() here
      as it will remove excess (not all) whitespaces only
    */
    current_line.erase(
      std::remove_if(current_line.begin(), current_line.end(), ::isspace),
      current_line.end()
    );

    if (current_line.empty() or current_line[0] == '#') {
      continue;
    }

    const size_t delimiter_pos = current_line.find('=');
    if (delimiter_pos == std::string_view::npos) {
      continue;
    }

    std::string key = current_line.substr(0, delimiter_pos);
    std::string value = current_line.substr(delimiter_pos + 1);
    set_property(key, value);
  }
}
