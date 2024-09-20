/*

This file is from Sysfex, another system info fetching tool

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <cctype> // for std::isspace
#include <unordered_map>
#include <unicode/uchriter.h>
#include <unicode/uchar.h>

static std::unordered_map<std::string, std::string> COLOR_VALUES = {
  {"\\b_black",     "\033[40m"  },
  {"\\b_red",       "\033[41m"  },
  {"\\b_green",     "\033[42m"  },
  {"\\b_yellow",    "\033[43m"  },
  {"\\b_blue",      "\033[44m"  },
  {"\\b_magenta",   "\033[45m"  },
  {"\\b_cyan",      "\033[46m"  },
  {"\\b_white",     "\033[47m"  },
  {"\\b_gray",      "\033[100m" },
  {"\\b_bred",      "\033[101m" },
  {"\\b_bgreen",    "\033[102m" },
  {"\\b_byellow",   "\033[103m" },
  {"\\b_bblue",     "\033[104m" },
  {"\\b_bmagenta",  "\033[105m" },
  {"\\b_bcyan",     "\033[106m" },
  {"\\b_bwhite",    "\033[107m" },
  {"\\f_black",     "\033[30m"  },
  {"\\f_red",       "\033[31m"  },
  {"\\f_green",     "\033[32m"  },
  {"\\f_yellow",    "\033[33m"  },
  {"\\f_blue",      "\033[34m"  },
  {"\\f_magenta",   "\033[35m"  },
  {"\\f_cyan",      "\033[36m"  },
  {"\\f_white",     "\033[37m"  },
  {"\\f_gray",      "\033[90m"  },
  {"\\f_bred",      "\033[91m"  },
  {"\\f_bgreen",    "\033[92m"  },
  {"\\f_byellow",   "\033[93m"  },
  {"\\f_bblue",     "\033[94m"  },
  {"\\f_bmagenta",  "\033[95m"  },
  {"\\f_bcyan",     "\033[96m"  },
  {"\\f_bwhite",    "\033[97m"  },
  {"\\reset",       "\033[0m"   },
  {"\\bold",        "\033[1m"   },
  {"\\faint",       "\033[2m"   },
  {"\\italic",      "\033[3m"   },
  {"\\underline",   "\033[4m"   },
  {"\\sblink",      "\033[5m"   },
  {"\\rblink",      "\033[6m"   },
  {"\\invert",      "\033[7m"   },
  {"\\hide",        "\033[8m"   },
  {"\\strike",      "\033[9m"   },
  {"\\primary",     "\033[10m"  },
  {"\\normal",      "\033[22m"  },
  {"\\noitalic",    "\033[23m"  },
  {"\\nounderline", "\033[24m"  },
  {"\\noblink",     "\033[25m"  },
  {"\\reveal",      "\033[28m"  },
  {"\\nostrike",    "\033[29m"  },
  {"\\df",          "\033[39m"  },
  {"\\db",          "\033[49m"  }
};

namespace sfUtils {

  size_t get_string_display_width(const std::string& line);

  std::string get_output_of(const char *command);

  std::string parse_string(const std::string &source, bool peel);

  std::string trim_string_spaces(const std::string& source);
  
}
