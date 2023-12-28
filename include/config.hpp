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
    {"text_beside_ascii",   "1"                         },
    {"ascii_path",          "/opt/sysfex/ascii/tux.txt" },
    {"color_block",         "⬤"                         },
    {"clear_screen",        "1"                         },
    {"gap",                 "10"                        },
    {"pregap",              "6"                         },
    {"starting_column",     "0"                         },
    {"starting_line",       "0"                         }
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
