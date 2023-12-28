/****************************************************/
/* This file is a part of Sysfex                    */
/* This function returns the used CPU by percentage */
/****************************************************/

#include <algorithm>
#include <fstream>
#include <modules/cpu.hpp>

std::string cpu() {
  std::string modelName = "model name", cpu = "";

  std::ifstream infile;
  infile.open("/proc/cpuinfo");               /* `/proc/cpuinfo` has a lot of info about the CPU(s) of your device */
  if (!infile.is_open()) {
    return "";
  }

  /* We need to go through `/proc/cpuinfo` until we get what we want */
  while (infile.good() and cpu == "") {
    std::string currentLine;
    std::getline(infile, currentLine);
    /*
      The line containing the model of the CPU has the keyword "model name"
      at it's beginning
      So looking for that specific keyword is enough
    */
    if (currentLine.find(modelName) != std::string::npos) {
      cpu = currentLine;
    }
  }
  infile.close();

  if (cpu == "") {
    return "";
  }

  /* Erase "model name" from output */
  cpu = cpu.substr(modelName.length(), cpu.length() - (modelName.length()));

  /* Remove leading spaces and separator from output */
  int trimFrom = 0;
  while (cpu[trimFrom] == ' ' or
         cpu[trimFrom] == '\t' or
         cpu[trimFrom] == ':') {
    trimFrom++;
  }
  cpu = cpu.substr(trimFrom);

  /* Remove clock speed from output */
  if (size_t pos = cpu.find('@'); pos != std::string::npos) {
    cpu = cpu.substr(0, pos);
  }

  return cpu;
}