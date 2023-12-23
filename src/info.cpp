#include <algorithm>
#include <filesystem>
#include <fstream>
#include <map>
#include "info.hpp"

Info sysfex_info;

Info *Info::the() {
  return &sysfex_info;
}

const std::pair<std::string, std::string> *Info::getInfos() {
  return infos;
}

int Info::getCurrentInfo() {
  return currentInfo;
}

void Info::setCurrentInfo(int new_currentInfo) {
  currentInfo = new_currentInfo;
}

int Info::getInfoSize() {
  return infoSize;
}

void Info::setInfoSize(int new_infoSize) {
  infoSize = new_infoSize;
}

void Info::init(std::string dir) {
  currentInfo = 0,
  infoSize = 0;

  if (!std::filesystem::exists(dir)) {
    return;
  }

  std::ifstream infile;
  infile.open(dir);
  while (infile.good()) {
    std::string type, currentLine;
    infile >> type;
    getline(infile, currentLine);

    // Comment
    if (type[0] == '#') {
      continue;
    }

    int leftInvertedComma = currentLine.find('"'),
        rightInvertedComma = currentLine.find_last_of('"');

    if (leftInvertedComma == std::string::npos or
        leftInvertedComma == rightInvertedComma) {
      continue;
    }

    if (type == "info") {
      std::string key, info;
      key = currentLine.substr(leftInvertedComma + 1, rightInvertedComma - (leftInvertedComma + 1));
      info = currentLine.substr(rightInvertedComma + 1, currentLine.back());
      /* Erase unnecessary whitespaces */
      info.erase(std::remove_if(info.begin(), info.end(), isspace), info.end());

      if (printables.find(info) == printables.end()) {
        continue;
      }

      infos[infoSize] = {key, (*printables.at(info))()};
      infoSize++;
    } else if (type == "print") {
      currentLine = currentLine.substr(leftInvertedComma + 1, rightInvertedComma - (leftInvertedComma + 1));
      infos[infoSize] = {currentLine, ""};
      infoSize++;
    }
  }
}