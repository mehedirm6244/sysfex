#include <fstream>
#include <sstream>

#include <modules/ram.hpp>

std::string ram() {
  int free_mem = 0;
  int total_mem = 0;
  int used_mem;
  int used_mem_perc;

  std::ifstream meminfo("/proc/meminfo");
  if (!meminfo.is_open()) {
    return "Unknown";
  }

  std::string key;
  while (meminfo >> key) {
    if (key == "MemTotal:") {
      meminfo >> total_mem;
    } else if (key == "MemAvailable:") {
      meminfo >> free_mem;
    }

    if (free_mem and total_mem) {
      break;
    }
  }
  meminfo.close();

  used_mem = total_mem - free_mem;
  used_mem_perc = (used_mem * 100) / total_mem;

  std::ostringstream output;

  output << std::to_string((used_mem) / 1024) << "MiB used " << "(" << std::to_string(used_mem_perc) << "%)";
  return output.str();
}
