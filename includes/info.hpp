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

#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <filesystem>
#include <fstream>

#include "modules.hpp"

class Info {
  
private:
  const std::vector<std::pair<std::string, std::string(*)()>> printables = {
    {"CPU", cpu},
    {"CPU_TEMP", cpu_temp},
    {"DE", de},
    {"DISTRO", distro},
    {"GPU", gpu},
    {"HOST", host},
    {"KERNEL", kernel},
    {"MODEL", model},
    {"OS", os},
    {"PKGS", pkgs},
    {"RAM", ram},
    {"RESOLUTION", resolution},
    {"SHELL", shell},
    {"SWAP", swap},
    {"UPTIME", uptime},
    {"USER", user}
  };

  const std::string default_config = R"(# Comments start with '#'

# Available variables:
#   'CPU', 'CPU_TEMP' 'DE', 'DISTRO', 'GPU', 'HOST', 'KERNEL', 'MODEL',
#   'OS', 'PKGS', 'RAM', 'RESOLUTION', 'SHELL', 'SWAP', 'UPTIME', 'USER'

"\bold{USER}@{HOST}\reset"
""
"\f_blue\boldModel    \reset {MODEL}"
"\f_blue\boldDistro   \reset {DISTRO}"
"\f_blue\boldKernel   \reset {KERNEL}"
"\f_blue\boldUptime   \reset {UPTIME}"
"\f_blue\boldPackages \reset {PKGS}"
"\f_blue\boldShell    \reset {SHELL}"
"\f_blue\boldDisplay  \reset {RESOLUTION}"
"\f_blue\boldDE       \reset {DE}"
"\f_blue\boldCPU      \reset {CPU}"
"\f_blue\boldGPU      \reset {GPU}"
"\f_blue\boldMemory   \reset {RAM}"
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
