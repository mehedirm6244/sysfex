#pragma once

#include <string>

void print(std::string key, std::string value);

void help();

std::string exec(const char *input);

size_t getLineWidth(const std::string &line);
