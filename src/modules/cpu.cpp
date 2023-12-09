/****************************************************/
/* This file is a part of Sysfex                    */
/* This function returns the used CPU by percentage */
/****************************************************/

#include <algorithm>
#include <fstream>
#include "cpu.hpp"

std::string cpu() {
    std::ifstream infile;
    infile.open("/proc/cpuinfo");
    std::string modelName = "model name", cpu = "";

    if (!infile.is_open()) {
        return "";
    }

    while (infile.good() and cpu == "") {
        std::string currentLine;
        std::getline(infile, currentLine);
        if (currentLine.find(modelName) != std::string::npos) {
            cpu = currentLine;
        }
    }
    infile.close();

    if (cpu == "") {
        return "";
    }

    cpu.erase(std::remove_if(cpu.begin(), cpu.end(), isspace),
              cpu.end());        /* Erase extra spaces from the output*/
    cpu = cpu.substr(modelName.length(), cpu.length() -
                                         (modelName.length()));      /* Erase the "model name" std::string before the output */
    if (size_t pos = cpu.find('@'); pos !=
                                    std::string::npos) {                        /* Remove clock speed from the output */
        cpu = cpu.substr(0, pos);
    }

    return cpu;
}