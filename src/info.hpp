#pragma once

#include <string>
#include <map>

#include "modules.hpp"

const std::map<std::string, std::string(*)()> printables = {
  {"host",         *(host)},
  {"os",           *(os)},
  {"kernel",       *(kernel)},
  {"pkgs",         *(pkgs)},
  {"shell",        *(shell)},
  {"model",        *(model)},
  {"user",         *(user)},
  {"de",           *(de)},
  {"ram",          *(ram)},
  {"uptime",       *(uptime)},
  {"resolution",   *(resolution)},
  {"cpu",          *(cpu)},
  {"colors_dark",  *(colors_dark)},
  {"colors_light", *(colors_light)}
};

class Info {
  std::pair<std::string, std::string> infos[64];
  int infoSize, currentInfo;

public:
  static Info *the();

  void init(std::string dir);

  const std::pair<std::string, std::string> *getInfos();

  int getCurrentInfo();

  void setCurrentInfo(int new_currentInfo);

  int getInfoSize();

  void setInfoSize(int new_infoSize);
};