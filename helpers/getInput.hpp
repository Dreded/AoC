#pragma once

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <array>

constexpr const char* COLOR_GREEN = "\033[1;32m";
constexpr const char* COLOR_CYAN = "\033[36m";
constexpr const char* COLOR_RED = "\033[31m";
constexpr const char* COLOR_YELLOW = "\033[33m";
constexpr const char* COLOR_RESET = "\033[0m";

inline constexpr std::array<const char*, 2> INPUT_FILES = {
    "example_input.txt",
    "puzzle_input.txt"
};
struct InputData
{
  std::vector<std::string> lines;
  int fileIndex;
};
InputData readFile(int file);
void header(const InputData& input);
