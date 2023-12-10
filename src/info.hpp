#pragma once

#include <string>
#include <map>

void initInfo(std::string dir);

const std::pair<std::string, std::string> *getInfos();

int getCurrentInfo();

void setCurrentInfo(int new_currentInfo);

int getInfoSize();

void setInfoSize(int new_infoSize);