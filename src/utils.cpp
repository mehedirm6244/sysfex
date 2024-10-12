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

#include "utils.hpp"

#include <array>
#include <cstring>
#include <iostream>
#include <memory>
#include <unicode/uchriter.h>
#include <unicode/uchar.h>
#include <unistd.h>
#include <sys/wait.h>

/*
  Execute a system command and return its output as std::string (only stdout)
  http://stackoverflow.com/questions/478898/ddg#478960
*/
std::string sfUtils::get_output_of(const std::string_view command) {
  std::array<char, 1024> buffer;
  std::string result;
  std::unique_ptr<FILE, void(*)(FILE*)> pipe(popen(command.data(), "r"),
    [](FILE *f) -> void {
    /* Wrapper to ignore the return value from pclose() is needed with newer versions of gnu g++ */
    std::ignore = pclose(f);
  });

  if (!pipe) {
    std::cerr << "popen() failed: " << std::strerror(errno);
    return "";
  }

  result.reserve(buffer.size());
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }

  if (!result.empty() and result.back() == '\n') {
    result.pop_back();
  }

  return result;
}

/* Compute the display width of a string considering wchars */
size_t sfUtils::get_string_display_width(const std::string_view line) {
  std::string peeled_line = parse_string(line, true);
  size_t string_display_width = 0;

  icu::UnicodeString unicode_string(peeled_line.c_str());
  const UChar *unicode_buffer = unicode_string.getTerminatedBuffer();
  icu::UCharCharacterIterator char_iterator(unicode_buffer, u_strlen(unicode_buffer));

  while (char_iterator.hasNext()) {
    UChar32 ch = char_iterator.next32();
    int width = u_getIntPropertyValue(ch, UCHAR_EAST_ASIAN_WIDTH);

    if (width == U_EA_FULLWIDTH or width == U_EA_WIDE) {
      string_display_width += 2;
    } else {
      string_display_width++;
    }
  }

  return string_display_width;
}

std::string sfUtils::parse_string(const std::string_view source, bool peel) {
  std::string parsed_string;
  std::string tmp_buf;

  for (auto ch: source) {
    if (!tmp_buf.empty() and ch == '\\' and tmp_buf.back() != '\\') {
      parsed_string += tmp_buf;
      tmp_buf = "";
    }

    tmp_buf += ch;
    if (COLOR_VALUES.find(tmp_buf) != COLOR_VALUES.end()) {
      if (!peel) {
        parsed_string += COLOR_VALUES[tmp_buf];
      }
      tmp_buf = "";
    }

    if (tmp_buf == "\\e" or tmp_buf == "\\033") {
      parsed_string += (char)27;
      tmp_buf = "";
    }
  }

  parsed_string += tmp_buf;
  return parsed_string;
}

/* Remove all whitespaces (' ', '\t', '\n') from a string */
std::string sfUtils::trim_string_spaces(std::string source) {
  std::string result;
  bool in_spaces = false;

  for (char ch : source) {
    if (std::isspace(ch)) {
      if (!in_spaces) {
        result += ' '; // Add only one space
        in_spaces = true;
      }
    } else {
      result += ch;
      in_spaces = false;
    }
  }

  /* Trim leading spaces */
  size_t start = result.find_first_not_of(" ");
  result = (start == std::string::npos) ? "" : result.substr(start);

  // Trim trailing spaces
  size_t end = result.find_last_not_of(" ");
  result = (end == std::string::npos) ? "" : result.substr(0, end + 1);

  return result;
}

/*
  Executes commands with execvp() and keep the program running without existing
  @param cmd_str The command to execute
  @return true if the command successed, else false
  @Original https://github.com/BurntRanch/TabAUR/blob/main/src/util.cpp#L484
*/
bool sfUtils::taur_exec(const std::vector<std::string_view> cmd_str) {
  std::vector<const char*> cmd;
  for (const std::string_view str : cmd_str) {
    cmd.push_back(str.data());
  }

  int pid = fork();

  if (pid < 0) {
    std::cerr << "fork() failed: " << strerror(errno);
  } else if (pid == 0) {
    cmd.push_back(nullptr);
    execvp(cmd.at(0), const_cast<char* const*>(cmd.data()));

    /* execvp() returns instead of exiting when failed */
    std::cerr << "An error has occurred: " << cmd.at(0) << ':' << strerror(errno);
  } else if (pid > 0) { // Wait for the command to finish then start executing the rest
    int status;
    waitpid(pid, &status, 0); // Wait for the child to finish

    if (WIFEXITED(status) and WEXITSTATUS(status) == 0) {
      return true;
    }
  }

  return false;
}
