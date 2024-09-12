#include <fstream>

#include <utils.hpp>
#include <modules/kernel.hpp>

std::string kernel() {
  std::ifstream release_file("/proc/sys/kernel/osrelease");
  if (!release_file.is_open()) {
    return get_output_of("uname -r"); // Fallback
  }

  std::string output;
  release_file >> output;
  release_file.close();

  return output;
}
