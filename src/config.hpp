/*************************************************/
/* This file is a part of Sysfex                 */
/* This file is for configuration related stuffs */
/*************************************************/

#pragma once

#include <map>
#include <string>

class Config {
  /*
    config[i].first = key
    config[i].second = value
  */
  std::map<std::string, std::string> config = {
    {"ascii",               "1"                         },
    {"ascii_beside_text",   "1"                         },
    {"ascii_path",          "/opt/sysfex/ascii/tux.txt" },
    {"bold_ascii",          "1"                         },
    {"bold_text",           "1"                         },
    {"color_block",         "⬤"                         },
    {"gap",                 "10"                        },
    {"pregap",              "6"                         },
    {"separator",           ":"                         },
    {"clear_screen",        "1"                         },
    {"starting_line",       "0"                         },
    {"starting_column",     "0"                         },
  };

public:
  static Config *the();

  /****************************/
  /* Assign something I guess */
  /****************************/
  void setValue(std::string key, std::string value);

  /*******************************/
  /* Get the value of a property */
  /*******************************/
  std::string getValue(std::string key);

  /*******************************/
  /* Initializes the config file */
  /*******************************/
  void init(std::string dir);
};
