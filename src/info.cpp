#include <algorithm>
#include <filesystem>
#include <fstream>

/* Sysfex headers */
#include <info.hpp>

Info sysfex_info;

Info *Info::the() {
  return &sysfex_info;
}

const std::vector<std::string> Info::get_info() {
  return infos;
}

size_t Info::get_info_size() {
  return infos.size();
}

void Info::init(const std::string& dir) {
  if (!std::filesystem::exists(dir)) {
    return;
  }

  std::ifstream infile(dir);
  if (!infile.is_open()) {
    return;
  }
  
  std::string current_line;
  while (std::getline(infile, current_line)) {
    /* Ignore comments and empty lines */
    if (current_line.empty() or current_line[0] == '#') {
      continue;
    }

    size_t left_quote = current_line.find('"');
    size_t right_quote = current_line.find_last_of('"');
    if (left_quote == std::string::npos or left_quote == right_quote) {
      continue;
    }
    current_line = current_line.substr(left_quote + 1, right_quote - left_quote - 1);

    for (auto &pair : printables) {
      std::string placeholder = "{" + pair.first + "}";
      size_t pos = current_line.find(placeholder);
      while (pos != std::string::npos) {
        current_line.replace(pos, placeholder.length(), pair.second());
        pos = current_line.find(placeholder, pos + pair.second().length());
      }
    }

    infos.push_back(current_line);
  }
}
