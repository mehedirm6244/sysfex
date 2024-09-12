/*
  Sysfex is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Sysfex is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Sysfex. If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <cstring>
#include <fstream>
#include <filesystem>

/* Sysfex headers */
#include <config.hpp>
#include <utils.hpp>
#include <shell_escape.hpp>
#include <info.hpp>
#include <image.hpp>

void import_config();
void sysfex_run();

int main(int argc, const char *argv[]) {
  /* Import config files from `~/.config/sysfex/` */
  import_config();

  /* Process command-line flags */
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--help") == 0) {
      print_help();
      return 0;
    }

    /* Flags requiring values should not be the last argument */
    if (i != argc - 1) {
      if (strcmp(argv[i], "--ascii") == 0) {
        Config::the()->set_property("ascii", argv[++i]);
      } else if (strcmp(argv[i], "--config") == 0) {
        Config::the()->init(argv[++i]);
      } else if (strcmp(argv[i], "--info") == 0) {
        Info::the()->init(argv[++i]);
      } else {
        std::cerr << RED << "Invalid flag: " << argv[i] << RESET << '\n';
        return 1;
      }
    } else {
      std::cerr << RED << "Invalid command format!" << RESET << '\n';
      std::cout << "Run `sysfex --help` for assistance.";
      return 1;
    }
  }

  sysfex_run();
  return 0;
}


/* Look for config files in `~/.config/sysfex/` */
void import_config() {
  const std::string local_conf_dir = std::string("/home/") + std::getenv("USER") + "/.config/sysfex/";

  if (!std::filesystem::exists(local_conf_dir)) {
    std::filesystem::create_directories(local_conf_dir);
  }

  /* Handle config file */
  const std::string local_config = local_conf_dir + "config";

  if (!std::filesystem::exists(local_config)) {
    Config::the()->generate_config_file(local_config);
  }
  
  Config::the()->init(local_config);

  /* Handle info file */
  const std::string local_info = local_conf_dir + "info";

  if (!std::filesystem::exists(local_info)) {
    Info::the()->generate_config_file(local_info);
  }

  Info::the()->init(local_info);
}


void sysfex_run() {
  size_t longest_line_width = 0;
  size_t line_count = 0;

  if (Config::the()->get_property("clear_screen") != "0") {
    std::system("clear");
  }

  /* Print ASCII if it exists */
  std::string ascii_path = Config::the()->get_property("ascii");
  if (std::filesystem::exists(ascii_path)) {
    if (is_supported_image(ascii_path)) {
      longest_line_width = std::stoi(Config::the()->get_property("image_width"));
      line_count = img_height_when_width(ascii_path, longest_line_width);

      preview_image(ascii_path, longest_line_width);
    } else {
      std::ifstream ascii_file(ascii_path);
      std::string current_line;

      while (std::getline(ascii_file, current_line)) {
        size_t current_line_width = get_string_display_width(current_line);
        longest_line_width = std::max(longest_line_width, current_line_width);
        std::cout << process_escape(current_line, false) << '\n';
        line_count++;
      }
    }
  } else {
    /* Useless to keep these true in this scenario */
    Config::the()->set_property("info_beside_ascii", "0");
    Config::the()->set_property("gap", "0");
  }

  /* Print information beside ASCII */

  if (Config::the()->get_property("info_beside_ascii") == "1") {
    /* TO FIX: if the ASCII file is bigger than the terminal window, */
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

    std::cout << process_escape(current_info, false) << '\n';
  }

  if (line_count > Info::the()->get_info_size() and
      Config::the()->get_property("info_beside_ascii") == "1") {
    size_t offset = line_count - Info::the()->get_info_size() - 1;
    std::cout << "\033[" << offset << "B";
  }
}
