#include <iostream>
#include <memory>
#include <unicode/uchriter.h>
#include <unicode/uchar.h>

/* Sysfex headers */
#include <config.hpp>
#include <utils.hpp>
#include <shell_escape.hpp>

void print_help() {
  Config::the()->set_property("gap", "0");

  std::cout << BOLD << "Sysfex" << UBOLD << " - another fetch tool written in C++\n\n";
  std::cout << BOLD << "Flags:" << UBOLD << '\n';
  std::cout << BOLD << "\t--help " << UBOLD << "Show this page\n";
  std::cout << BOLD << "\t--ascii <path> " << UBOLD << "Specify the ASCII file\n";
  std::cout << BOLD << "\t--config <path> " << UBOLD << "Specify the `config` file\n";
  std::cout << BOLD << "\t--info <path> " << UBOLD << "Specify the `info` file\n";
}

/* Execute a system command and return its output as std::string */
std::string get_output_of(const char *command) {
  std::unique_ptr<FILE, decltype(&pclose)> stream { popen(command, "r"), &pclose };
  std::string output;

  if (stream) {
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), stream.get()) != nullptr) {
      output.append(buffer);
    }
  }

  if (!output.empty() and output.back() == '\n') {
    output.pop_back();
  }

  return output;
}

/* Compute the display width of a string considering wchars */
size_t get_string_display_width(const std::string& line) {
  std::string peeled_line = process_escape(line, true);
  size_t string_display_width = 0;

  icu::UnicodeString unicode_string(peeled_line.c_str());
  const UChar *unicode_buffer = unicode_string.getTerminatedBuffer();
  icu::UCharCharacterIterator char_iterator(unicode_buffer, u_strlen(unicode_buffer));

  while (char_iterator.hasNext()) {
    UChar32 ch = char_iterator.next32();
    int width = u_getIntPropertyValue(ch, UCHAR_EAST_ASIAN_WIDTH);

    if (width == U_EA_FULLWIDTH || width == U_EA_WIDE) {
      string_display_width += 2;
    } else {
      string_display_width++;
    }
  }

  return string_display_width;
}
