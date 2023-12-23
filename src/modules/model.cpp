/*************************************************/
/* This file is a part of Sysfex                 */
/* This function returns the model of the device */
/*************************************************/

#include <fstream>
#include "model.hpp"

std::string model() {
  std::string modelName, version;
  std::ifstream infile;

  /* `/sys/devices/virtual/dmi/id/product_name` contains your device's name */
  infile.open("/sys/devices/virtual/dmi/id/product_name");
  if (!infile.is_open()) {
    return "";
  }
  getline(infile, modelName);
  infile.close();

  /* `/sys/devices/virtual/dmi/id/product_version` contains your device's version */
  infile.open("/sys/devices/virtual/dmi/id/product_version");
  if (!infile.is_open()) {
    return "";
  }
  getline(infile, version);
  infile.close();

  std::string output = modelName + " " + version;
  return output;
}