#include <fstream>

#include <modules/os.hpp>

std::string os() {
  std::ifstream infile("/etc/os-release");
  if (!infile.is_open()) {
    return "Unknown";
  }

  std::string output;
  std::string pretty_name = "PRETTY_NAME=\"";

  while (std::getline(infile, output)) {
    if (output.find(pretty_name) != std::string::npos) {
      break;
    }
  }
  infile.close();

  if (output.empty()) {
    return "Unknown";
  }

  /* Remove "PRETTY_NAME" from output */
  output = output.substr(pretty_name.length(), output.length() - (pretty_name.length() + 1));
  return output;
}
