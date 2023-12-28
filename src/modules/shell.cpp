/****************************************************/
/* This file is a part of Sysfex              			*/
/* This function returns the shell used by the user */
/****************************************************/

#include <modules/shell.hpp>

std::string shell() {
  /* Return the environment variable ${SHELL} */
  return std::string(std::getenv("SHELL"));
}