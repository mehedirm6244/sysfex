#pragma once

#include <string>

size_t getLineWidth(const std::string &line);

std::string getOutputOf(const char *input);

void help();

void print(std::string key, std::string value);
