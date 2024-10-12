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

#include "sysfex.hpp"
#include "utils.hpp"
#include "image.hpp"
#include "config.hpp"
#include "info.hpp"

#include <iostream>
#include <cstring>
#include <fstream>
#include <filesystem>
#include <string_view>

void Sysfex::about() {
  constexpr std::string_view about_text = R"(
███████╗██╗   ██╗███████╗███████╗███████╗██╗  ██╗
██╔════╝╚██╗ ██╔╝██╔════╝██╔════╝██╔════╝╚██╗██╔╝
███████╗ ╚████╔╝ ███████╗█████╗  █████╗   ╚███╔╝ 
╚════██║  ╚██╔╝  ╚════██║██╔══╝  ██╔══╝   ██╔██╗ 
███████║   ██║   ███████║██║     ███████╗██╔╝ ██╗
╚══════╝   ╚═╝   ╚══════╝╚═╝     ╚══════╝╚═╝  ╚═╝
                                                 
\boldSysfex\reset is just another system information fetching tool written in C++.
Report bugs: \f_green\underlinehttps://github.com/mehedirm6244/sysfex/issues\reset
  )";

  std::cout << sfUtils::parse_string(about_text, false);
}

void Sysfex::import_config(const bool init_config, const bool init_info) {
  const char* env = std::getenv("XDG_CONFIG_HOME");
  const std::filesystem::path& local_config = (env != nullptr) ?
    env : std::filesystem::path(std::getenv("HOME")) / ".config";
  const std::filesystem::path& sysfex_conf_path = local_config / "sysfex";
  const std::filesystem::path& sysfex_local_conf = sysfex_conf_path / "config";
  const std::filesystem::path& sysfex_local_info = sysfex_conf_path / "info";

  if (!std::filesystem::exists(sysfex_conf_path)) {
    std::filesystem::create_directories(sysfex_conf_path);
  }
  
  if (!std::filesystem::exists(sysfex_local_conf)) {
    Config::the()->generate_config_file(sysfex_local_conf.string());
  }

  if (!std::filesystem::exists(sysfex_local_info)) {
    Info::the()->generate_config_file(sysfex_local_info.string());
  }
  
  if (init_config) {
    Config::the()->init(sysfex_local_conf.string());
  }
  
  if (init_info) {
    Info::the()->init(sysfex_local_info.string());
  }
}

void Sysfex::help() {
  constexpr std::string_view help_text = R"(\boldUsage:\reset
  \bold-b, --about\reset          About Sysfex
  \bold-h, --help\reset           Show this page
  \bold-a, --ascii  <path>\reset  Specify ASCII/image
  \bold-C, --config <path>\reset  Specify `config` file
  \bold-i, --info   <path>\reset  Specify `info` file
  )";

  std::cout << sfUtils::parse_string(help_text, false);
}

void Sysfex::run() {
  if (Config::the()->get_property("clear_screen") != "0") {
    sfUtils::taur_exec({ "sh", "-c", "clear" });
  }

  const std::filesystem::path ascii_path = Config::the()->get_property("ascii");
  size_t longest_line_width = std::stoi(Config::the()->get_property("image_width"));
  size_t line_count = sfImage::img_height_when_width(ascii_path, longest_line_width);

  if (std::filesystem::exists(ascii_path)) {
    if (line_count != 0) {
      /* It must be an image */
      sfImage::preview_image(ascii_path, longest_line_width);
    } else {
      /* Treat it as an ASCII file */
      longest_line_width = 0;
      line_count = 0;
      std::ifstream ascii_file(ascii_path);
      std::string current_line;

      while (std::getline(ascii_file, current_line)) {
        const size_t current_line_width = sfUtils::get_string_display_width(current_line);
        longest_line_width = std::max(longest_line_width, current_line_width);
        std::cout << sfUtils::parse_string(current_line, false) << '\n';
        line_count++;
      }
    }
  } else {
    /* For better output format */
    Config::the()->set_property("info_beside_ascii", "0");
    Config::the()->set_property("gap", "0");
  }

  /* Handle the case where information is printed beside ASCII */
  bool info_beside_ascii = (Config::the()->get_property("info_beside_ascii") == "1");
  if (info_beside_ascii) {
    /* TO FIX: If ASCII is bigger than terminal window */
    std::cout << "\033[" << line_count << "A";
  }
  
  for (const auto& current_info : Info::the()->get_info()) {
    if (info_beside_ascii) {
      size_t offset = longest_line_width + stoi(Config::the()->get_property("gap"));
      if (std::filesystem::exists(ascii_path)) {
        offset++;
      }
      std::cout << "\033[" << offset << "C";
    }

    std::cout << sfUtils::parse_string(current_info, false) << '\n';
  }

  if (line_count > Info::the()->get_info_size() and info_beside_ascii) {
    const size_t offset = line_count - Info::the()->get_info_size() - 1;
    std::cout << "\033[" << offset << "B";
  }
}
