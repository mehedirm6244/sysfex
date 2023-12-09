#include <algorithm>
#include <filesystem>
#include <fstream>
#include <map>
#include <string>
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

std::pair<std::string, std::string> infos[64];
int infoSize, currentInfo;

const std::pair<std::string, std::string> *getInfos() {
    return infos;
}

int getCurrentInfo() {
    return currentInfo;
}

void setCurrentInfo(int new_currentInfo) {
    currentInfo = new_currentInfo;
}

int getInfoSize() {
    return infoSize;
}

void setInfoSize(int new_infoSize) {
    infoSize = new_infoSize;
}

void initInfo(std::string dir) {
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

        if (
                leftInvertedComma == std::string::npos or
                leftInvertedComma == rightInvertedComma
                )
            continue;

        if (type == "info") {
            std::string key = currentLine.substr(leftInvertedComma + 1, rightInvertedComma - (leftInvertedComma + 1)),
                    info = currentLine.substr(rightInvertedComma + 1, currentLine.back());
            // Erase extra spaces
            info.erase(std::remove_if(info.begin(), info.end(), isspace), info.end());

            if (printables.find(info) == printables.end())
                continue;

            infos[infoSize] = {key, (*printables.at(info))()};
            infoSize++;
        } else if (type == "print") {
            currentLine = currentLine.substr(leftInvertedComma + 1, rightInvertedComma - (leftInvertedComma + 1));
            infos[infoSize] = {currentLine, ""};
            infoSize++;
        }

        if (infoSize >= 64) {
            break;
        }
    }
}