#include "getInput.hpp"

InputData readFile(int file)
{
  InputData input;
  input.fileIndex = file;
  
  std::vector<std::string> lines;
  std::ifstream myfile(INPUT_FILES.at(file));
  if (!myfile.is_open())
  {
    std::cout << "Unable to open file";
    return input;
  }
  std::string line;
  while (getline(myfile, line))
  {
    input.lines.push_back(line);
  }

  return input;
}

void header(const InputData& input)
{
  std::filesystem::path cwd = std::filesystem::current_path();

  // cwd = .../2025/Day_01
  std::string dayFolder = cwd.filename().string();
  std::string yearFolder = cwd.parent_path().filename().string();

  int day = 0;
  int year = 0;

  // Extract numbers
  if (dayFolder.rfind("Day_", 0) == 0) {
    day = std::stoi(dayFolder.substr(4));
  }

  year = std::stoi(yearFolder);
  printf("%s\n", COLOR_GREEN);
  printf("╔══════════════════════════════════════╗\n");
  printf("║  Advent of Code %s%d      %sDay %s%02d%s     ║\n", COLOR_CYAN, year, COLOR_GREEN, COLOR_CYAN, day, COLOR_GREEN);
  printf("║  Input: %s%-28s %s║\n", COLOR_CYAN, INPUT_FILES.at(input.fileIndex), COLOR_GREEN);
  printf("║  Lines: %s%-28zu %s║\n", COLOR_CYAN, input.lines.size(), COLOR_GREEN);
  printf("╚══════════════════════════════════════╝\n\n%s", COLOR_RESET);
}
