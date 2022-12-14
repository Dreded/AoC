#include "getInput.hpp"

std::vector<std::string> readFile(int file)
{
  std::vector<std::string> lines;
  std::string files[] = {"example_input.txt","puzzle_input.txt"};
  std::ifstream myfile(files[file]);
  if (myfile.is_open())
  {
    std::string line;
    while (getline(myfile, line))
    {
      lines.push_back(line);
    }
    myfile.close();
  }

  else
    std::cout << "Unable to open file";
  return lines;
}