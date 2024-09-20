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

void Sysfex::about() {
  std::cout << sfUtils::parse_string("\
\\boldSysfex\\reset is just another system information fetching tool written in C++.\n\
\
Report bugs: https://github.com/mehedirm6244/sysfex/issues\n\
  ", false);
}

void Sysfex::import_config() {
  const std::filesystem::path local_config = (std::getenv("XDG_CONFIG_HOME") != nullptr) ?
    std::string(std::getenv("XDG_CONFIG_HOME")) : std::string("/home/") + std::getenv("USER") + "/.config";
  const std::filesystem::path sysfex_conf_path = local_config / "sysfex";
  const std::filesystem::path sysfex_local_conf = sysfex_conf_path / "config";
  const std::filesystem::path sysfex_local_info = sysfex_conf_path / "info";

  if (!std::filesystem::exists(sysfex_conf_path)) {
    std::filesystem::create_directories(sysfex_conf_path);
  }
  
  if (!std::filesystem::exists(sysfex_local_conf)) {
    Config::the()->generate_config_file(sysfex_local_conf);
  }

  if (!std::filesystem::exists(sysfex_local_info)) {
    Info::the()->generate_config_file(sysfex_local_info);
  }
  
  Config::the()->init(sysfex_local_conf);
  Info::the()->init(sysfex_local_info);
}

void Sysfex::help() {
  std::cout << sfUtils::parse_string("\
\\boldUsage:\\reset\n\
  \\bold--about\\reset About Sysfex\n\
  \\bold--help\\reset Show this page\n\
  \\bold--ascii <path>\\reset Specify ASCII/image\n\
  \\bold--config <path>\\reset Specify `config` file\n\
  \\bold--info <path>\\reset Specify `info` file\n\
  ", false);
}

void Sysfex::run() {
  size_t longest_line_width = 0;
  size_t line_count = 0;

  if (Config::the()->get_property("clear_screen") != "0") {
    std::system("clear");
  }

  /* Print ASCII if it exists */
  std::filesystem::path ascii_path = Config::the()->get_property("ascii");
  if (std::filesystem::exists(ascii_path)) {
    if (sfImage::is_supported_image(ascii_path)) {
      longest_line_width = std::stoi(Config::the()->get_property("image_width"));
      line_count = sfImage::img_height_when_width(ascii_path, longest_line_width);

      sfImage::preview_image(ascii_path, longest_line_width);
    } else {
      std::ifstream ascii_file(ascii_path);
      std::string current_line;

      while (std::getline(ascii_file, current_line)) {
        size_t current_line_width = sfUtils::get_string_display_width(current_line);
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

  /* Print information beside ASCII */

  if (Config::the()->get_property("info_beside_ascii") == "1") {
    /* TO FIX: If ASCII is bigger than terminal window */
    std::cout << "\033[" << line_count << "A";
  }
  
  for (const auto& current_info : Info::the()->get_info()) {
    if (Config::the()->get_property("info_beside_ascii") == "1") {
      size_t offset = longest_line_width + stoi(Config::the()->get_property("gap"));
      if (std::filesystem::exists(ascii_path)) {
        offset++;
      }
      std::cout << "\033[" << offset << "C";
    }

    std::cout << sfUtils::parse_string(current_info, false) << '\n';
  }

  if (line_count > Info::the()->get_info_size() and
      Config::the()->get_property("info_beside_ascii") == "1") {
    size_t offset = line_count - Info::the()->get_info_size() - 1;
    std::cout << "\033[" << offset << "B";
  }
}
