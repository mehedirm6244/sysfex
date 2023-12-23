#pragma once

#include <string>

void print(const std::string& key, const std::string& value);

void help();

std::string exec(const char *input);

size_t get_line_width(const std::string &line);
