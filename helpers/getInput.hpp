#pragma once

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>

std::vector<std::string> readFile(std::filesystem::path folder, int file);
