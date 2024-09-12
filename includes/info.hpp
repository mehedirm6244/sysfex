#pragma once

#include <vector>
#include <string>

#include "modules.hpp"

class Info {
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

  const char* default_config = R"(# Comments start with '#'

# Available variables:
#   'HOST', 'OS', 'KERNEL', 'PKGS', 'SHELL', 'MODEL',
#   'USER', 'DE', 'RAM', 'UPTIME', 'RESOLUTION', 'CPU'

"\bold{USER}@{HOST}\reset"
""
"\f_blue\boldDistro   \reset {OS}"
"\f_blue\boldKernel   \reset {KERNEL}"
"\f_blue\boldDE       \reset {DE}"
"\f_blue\boldUptime   \reset {UPTIME}"
"\f_blue\boldMemory   \reset {RAM}"
"\f_blue\boldCPU      \reset {CPU}"
"\f_blue\boldDisplay  \reset {RESOLUTION}"
"\f_blue\boldPackages \reset {PKGS}"
"\f_blue\boldShell    \reset {SHELL}"
""
"\b_black  \b_red  \b_green  \b_yellow  \b_blue  \b_magenta  \b_cyan  \b_white  \reset"
)";

  std::vector<std::string> infos;

public:
  static Info *the();

  void init(const std::string& dir);

  const std::vector<std::string>& get_info();

  void generate_config_file(const std::string& path);

  size_t get_info_size();
};
