/********************************************/
/* This file is a part of Sysfex            */
/* This function returns the username       */
/* This is a useless function, but anyway   */
/********************************************/

#include "user.hpp"

std::string user() {
  /* Return environment variable ${USER} */
  return std::getenv("USER");
}