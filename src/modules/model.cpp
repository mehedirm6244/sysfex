/*************************************************/
/* This file is a part of Sysfex                 */
/* This function returns the model of the device */
/*************************************************/

#include <fstream>
#include "model.hpp"

std::string model() {
    std::string name, version;
    std::ifstream infile;

    infile.open("/sys/devices/virtual/dmi/id/product_name");
    if (!infile.is_open()) {
        return "";
    }
    getline(infile, name);
    infile.close();

    infile.open("/sys/devices/virtual/dmi/id/product_version");
    if (!infile.is_open()) {
        return "";
    }
    getline(infile, version);
    infile.close();

    std::string s = name + " " + version;
    return s;
}