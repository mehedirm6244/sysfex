#include <algorithm>
#include <filesystem>
#include <fstream>

/* Sysfex headers */
#include <config.hpp>

Config sysfex_config;

Config *Config::the() {
  return &sysfex_config;
}

void Config::set_property(const std::string& key, const std::string& value) {
  if (config.find(key) != config.end()) {
    config[key] = value;
  }
}

std::string Config::get_property(const std::string& key) {
  if (config.find(key) != config.end()) {
    return config[key];
  }
  return "";
}

void Config::generate_config_file(const std::string& path) {
  std::ofstream generated_file(path);
  generated_file << default_config;
  generated_file.close();
}

void Config::init(const std::string& dir) {
  if (!std::filesystem::exists(dir)) {
    return;
  }

  std::ifstream config_file(dir);
  if (!config_file.is_open()) {
    return;
  }

  std::string current_line;
  while (std::getline(config_file, current_line)) {
    /* Trim spaces */
    current_line.erase(std::remove_if(current_line.begin(), current_line.end(), isspace), current_line.end());

    /* Ignore comments and empty lines */
    if (current_line[0] == '#' or current_line.empty()) {
      continue;
    }

    /* Find delimiter '=' and split key and value */
    size_t delimiter = current_line.find('=');
    std::string key = current_line.substr(0, delimiter);
    std::string value = current_line.substr(delimiter + 1);
    set_property(key, value);
  }
}
