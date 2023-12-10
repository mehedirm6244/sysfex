#pragma once

#include <string>

void print(std::string key, std::string value);

void help();

std::string exec(const char *input);

size_t get_line_width(const std::string &line);
