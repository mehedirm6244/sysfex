#include <modules/user.hpp>

/* Return environment variable ${USER} */
std::string user() {
  return std::getenv("USER");
}
