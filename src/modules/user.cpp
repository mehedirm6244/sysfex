/********************************************/
/* This file is a part of Sysfex            */
/* This function returns the username       */
/* This is an useless function, but anyways */
/********************************************/

#include "user.hpp"

std::string user() {
    return std::getenv("USER");
}