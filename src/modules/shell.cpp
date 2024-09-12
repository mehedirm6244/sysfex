#include <modules/shell.hpp>

/* Return the environment variable ${SHELL} */
std::string shell() {
  return std::getenv("SHELL");
}
