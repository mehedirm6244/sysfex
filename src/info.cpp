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

#include "info.hpp"

Info sysfex_info;

Info *Info::the() {
  return &sysfex_info;
}

const std::vector<std::string>& Info::get_info() {
  return infos;
}

size_t Info::get_info_size() {
  return infos.size();
}

void Info::generate_config_file(const std::string_view path) {
  std::ofstream generated_file(path.data());
  generated_file << default_config;
  generated_file.close();
}

void Info::init(const std::string_view dir) {
  if (!std::filesystem::exists(dir)) {
    return;
  }

  std::ifstream infile(dir.data());
  if (!infile.is_open()) {
    return;
  }
  
  std::string current_line;
  while (std::getline(infile, current_line)) {
    /* Ignore comments and empty lines */
    if (current_line.empty() or current_line[0] == '#') {
      continue;
    }

    const size_t left_quote = current_line.find('"');
    const size_t right_quote = current_line.find_last_of('"');
    if (left_quote == std::string::npos or left_quote == right_quote) {
      continue;
    }
    current_line = current_line.substr(left_quote + 1, right_quote - left_quote - 1);

    for (auto &pair : printables) {
      const std::string& placeholder = "{" + pair.first + "}";
      size_t pos = current_line.find(placeholder);
      while (pos != std::string::npos) {
        const std::string& info = pair.second();
        const size_t info_length = info.length();
        current_line.replace(pos, placeholder.length(), info);
        pos = current_line.find(placeholder, pos + info_length);
      }
    }

    infos.push_back(current_line);
  }
}
