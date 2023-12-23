#pragma once
#define BOLD    "\033[1m"
#define UBOLD   "\033[0m"

std::string process_escape(const std::string &source, bool peel);