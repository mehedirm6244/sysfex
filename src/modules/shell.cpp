/****************************************************/
/* This file is a part of Sysfex              			*/
/* This function returns the shell used by the user */
/****************************************************/

#include "shell.hpp"

std::string shell() {
    return std::string(std::getenv("SHELL"));
}