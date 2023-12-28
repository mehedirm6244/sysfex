/************************************************/
/* This file is a part of Sysfex                */
/* This function returns the name of the distro */
/************************************************/

#include <fstream>
#include <modules/os.hpp>

std::string os() {
  std::string output = "", prettyName = "PRETTY_NAME=\"";

  std::ifstream infile;
  infile.open("/etc/os-release");       /* /etc/os-release has stuffs about the distro that you're using */
  if (!infile.is_open()) {
    return "";
  }

  /*
    We'll search for the keyword "PRETTY_NAME" through the
    /etc/os-release file. The line containing is keyword should
    look like this:
      PRETTY_NAME="Linux Distro"
  */
  while (infile.good()) {
    std::getline(infile, output);
    if (output.find(prettyName) != std::string::npos) {
      break;
    }
  }
  infile.close();

  if (output == "") {
    return "";
  }

  /* Remove "PRETTY_NAME" from output */
  output = output.substr(prettyName.length(), output.length() - (prettyName.length() + 1));
  return output;
}