#include <algorithm>
#include <iostream>
#include <memory>
#include <unicode/uchriter.h>
#include <unicode/uchar.h>
#include "config.hpp"
#include "utils.hpp"
#include "shell_escape.hpp"

void print(const std::string& key, const std::string& value) {
    int keySize = (int)getLineWidth(key);

    int gap, pregap, remainingSpace;
    gap = stoi(Config::the()->getValue("gap"));
    pregap = stoi(Config::the()->getValue("pregap"));
    remainingSpace = std::max(1, gap - keySize);

    if (Config::the()->getValue("ascii_beside_text") != "0" and
        Config::the()->getValue("ascii") != "0") {
        std::cout << std::string(pregap, ' ');
    }

    if (Config::the()->getValue("bold_text") != "0") {
        std::cout << BOLD << process_escape(key, false) << UBOLD;
    } else {
        std::cout << process_escape(key, false);
    }

    if (!value.empty()) {
        if (!key.empty()) {
            std::cout << std::string(remainingSpace, ' ') << process_escape(Config::the()->getValue("separator"), false) << " ";
        }
        std::cout << process_escape(value, false);
    }

    std::cout << std::endl;
}


void help() {
    Config::the()->setValue("pregap", "0");
    Config::the()->setValue("gap", "0");

    std::cout << BOLD << "Sysfex" << UBOLD << " - another fetch tool written in C++\n" << std::endl;
    std::cout << BOLD << "Flags:" << UBOLD << std::endl;
    print("--help", "Print this screen");
    print("--ascii <value>", "If value == 0, don't print the ascii art, else do");
    print("--ascii-path <path-to-ascii>", "Specify the directory from where the ascii will be printed");
    print("--ascii-beside-txt <value>", "Choose whether the ascii will be printed beside info or not");
    print("--config <path-to-config>",
          "Specify the file which you want to be used as the config file");
    print("--info <path-to-printables>", "Specify the file from which info will be printed");
}


// Something which lets one to get the output of a command as a std::string
// I forgot where I collected this code from :( thanks anon
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
            // TODO: find out if characters that take more space than 2 columns exist
            length += 2;
        } else {
            length += 1;
        }
    }

    return length;
}
