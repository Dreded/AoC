#include "../../helpers/getInput.hpp"
#include "../../helpers/timer.hpp"

enum FileType { EXAMPLE_FILE, PUZZLE_FILE, CUSTOM_EXAMPLE_FILE };

void printTotal(long long total)
{
  static int calls = 1;
  printf("Part %i Answer: %lld\n", calls,total);
  calls++;
}

void part1(const InputData& input)
{
  ScopedTimer timer("Part 1");
  long long total = 0;
  for (const auto& line : input.lines)
  {
    printf("%s\n", line.c_str());
  }
  printTotal(total);
}

void part2(const InputData& input)
{
  ScopedTimer timer("Part 2");
  long long total = 0;
  for (const auto& line : input.lines)
  {
    printf("%s\n", line.c_str());
  }
  printTotal(total);
}

int main(int argc, char **argv)
{
  ScopedTimer timer("Main");
  int file = EXAMPLE_FILE; // default

  if (argc > 1)
  {
    try
    {
      file = std::stoi(argv[1]);
    } catch (...) {
      std::cerr << "Invalid file index, using EXAMPLE_FILE\n";
    }
  }

  InputData input = readFile(file);
  header(input);
  part1(input);
  part2(input);
  return 0;
}
