#include <algorithm>
#include <fstream>
#include <cctype> // for std::isspace

#include <modules/cpu.hpp>

std::string cpu() {
  std::string model_name = "model name";
  std::string output;

  std::ifstream cpu_info("/proc/cpuinfo");
  if (!cpu_info.is_open()) {
    return "Unknown";
  }

  while (cpu_info.good()) {
    std::string current_line;
    std::getline(cpu_info, current_line);

    if (current_line.find(model_name) != std::string::npos) {
      output = current_line;
      break;
    }
  }
  cpu_info.close();

  if (output.empty()) {
    return "Unknown";
  }

  /* Erase "model name" from output */
  output = output.substr(model_name.length());

  /* Trim leading spaces and colon */
  output.erase(output.begin(), std::find_if(output.begin(), output.end(), [](unsigned char ch) {
    return !std::isspace(ch) && ch != ':';
  }));

  /* Remove clock speed from output */
  if (size_t pos = output.find('@'); pos != std::string::npos) {
    output = output.substr(0, pos);
  }

  return output;
}
