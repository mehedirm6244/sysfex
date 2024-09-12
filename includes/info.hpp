#pragma once

#include <vector>
#include <string>

#include "modules.hpp"

const std::vector<std::pair<std::string, std::string(*)()>> printables = {
  {"HOST", host},
  {"OS", os},
  {"KERNEL", kernel},
  {"PKGS", pkgs},
  {"SHELL", shell},
  {"MODEL", model},
  {"USER", user},
  {"DE", de},
  {"RAM", ram},
  {"UPTIME", uptime},
  {"RESOLUTION", resolution},
  {"CPU", cpu}
};

class Info {
  std::vector<std::string> infos;

public:
  static Info *the();

  void init(const std::string& dir);

  const std::vector<std::string> get_info();

  size_t get_info_size();
};
