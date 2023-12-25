#include <fstream>
#include <map>

std::map<std::string, std::string> COLOR_VALUES = {
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

std::string process_escape(const std::string &source, bool peel) {
  std::string processed_art;
  std::string tmp_buf;

  for (auto ch: source) {
    if (!tmp_buf.empty() and ch == '\\' and tmp_buf.back() != '\\') {
      processed_art += tmp_buf;
      tmp_buf = "";
    }

    tmp_buf += ch;
    if (COLOR_VALUES.find(tmp_buf) != COLOR_VALUES.end()) {
      if (!peel) {
        processed_art += COLOR_VALUES[tmp_buf];
      }
      tmp_buf = "";
    }

    if (tmp_buf == "\\e" or tmp_buf == "\\033") {
      processed_art += (char)27;
      tmp_buf = "";
    }
  }

  processed_art += tmp_buf;
  return processed_art;
}
