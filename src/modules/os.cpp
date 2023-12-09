/************************************************/
/* This file is a part of Sysfex                */
/* This function returns the name of the distro */
/************************************************/

#include <fstream>
#include "os.hpp"

std::string os() {
    std::string name = "", prettyName = "PRETTY_NAME=\"";

    std::ifstream infile;
    infile.open("/etc/os-release");
    if (!infile.is_open())
        return "";

    while (infile.good()) {
        std::getline(infile, name);
        if (name.find(prettyName) != std::string::npos) {
            break;
        }
    }
    infile.close();

    if (name == "") {
        return "";
    }

    /* Remove "PRETTY_NAME" and stuffs from the std::string */
    name = name.substr(prettyName.length(), name.length() - (prettyName.length() + 1));
    return name;
}