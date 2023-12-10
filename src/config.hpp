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
    std::map<std::string, std::string> config;

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
