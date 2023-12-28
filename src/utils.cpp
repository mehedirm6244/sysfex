#include <algorithm>
#include <iostream>
#include <memory>
#include <unicode/uchriter.h>
#include <unicode/uchar.h>
#include <config.hpp>
#include <utils.hpp>
#include <shell_escape.hpp>


void help() {
  Config::the()->setValue("pregap", "0");
  Config::the()->setValue("gap", "0");

  /* TODO: Do something with this mess */
  std::cout << BOLD << "Sysfex" << UBOLD << " - another fetch tool written in C++\n" << '\n';
  std::cout << BOLD << "Flags:" << UBOLD << '\n';
  std::cout << BOLD << "\t--help " << UBOLD << "Print this page" << '\n';
  std::cout << BOLD << "\t--ascii-path <path> " << UBOLD << "Specify the directory from where the ascii will be printed" << '\n';
  std::cout << BOLD << "\t--config <path> " << UBOLD << "Specify the file which you want to be used as the config file" << '\n';
  std::cout << BOLD << "\t--info <path> " << UBOLD << "Specify the file from which info will be printed" << '\n';
}


/*
  Something which lets one get the output of a command as a std::string
  I forgot where I collected this code from :( thanks anon
*/
std::string getOutputOf(const char *input) {
  std::unique_ptr<FILE, decltype(&pclose)> stream{popen(input, "r"), &pclose};
  std::string output;
  if (stream) {
    while (!feof(stream.get())) {
      auto offset = output.size();
      output.resize(output.size() + 256);

      if (fgets(output.data() + offset, output.size() - offset, stream.get()) == NULL) {
        break;
      }

      if (ferror(stream.get())) {
        output.resize(offset);
        break;
      }

      output.resize(std::distance(output.begin(), std::find(output.begin() + offset, output.end(), '\0') - 1));
    }
  }

  if (output.back() == '\n') {
    output.pop_back();
  }

  return output;
}

size_t getLineWidth(const std::string &line) {
  std::string peeled_line = process_escape(line, true);
  size_t length = 0;
  icu::UnicodeString us(peeled_line.c_str());
  const UChar *us_buf = us.getTerminatedBuffer();
  icu::UCharCharacterIterator it(us_buf, u_strlen(us_buf));

  while (it.hasNext()) {
    int width = u_getIntPropertyValue(it.next(), UCHAR_EAST_ASIAN_WIDTH);
    if (width == U_EA_FULLWIDTH || width == U_EA_WIDE) {
      /* TODO: find out if characters that take more space than 2 columns exist */
      length += 2;
    } else {
      length += 1;
    }
  }

  return length;
}
