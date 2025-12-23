#include "../../helpers/getInput.hpp"
#include "../../helpers/timer.hpp"

enum FileType { EXAMPLE_FILE, PUZZLE_FILE };

void printTotal(int total)
{
    static int calls = 1;
    printf("Part %i Total: %i\n", calls,total);
    calls++;
}

struct Rotation { int d, a; }; // direction/amount

int moveDial(int current, const Rotation& r)
{
  return (current + r.d * r.a) % 100;
}

int countZeroCrosses(int dial, const Rotation& r)
{
  int zeroCrosses = 0;

  //simulate every click
  for (int i = 0; i < r.a; ++i)
  {
    dial = (dial + r.d) % 100;
    if (dial == 0) zeroCrosses++;
  }
  return zeroCrosses;
}

//in part 1 we need to count he times the dial points at zero
void part1(const std::vector<Rotation>& rotations)
{
  ScopedTimer timer("Part 1");
  // We have a Safe Dial that has numbers 0-99 and starts pointing at 50
  int total = 0;
  int dial = 50;
  for (const auto& r : rotations)
    if ((dial = moveDial(dial, r)) == 0) ++total;
  printTotal(total);
}

//in part 2 we need to count the times the dial crosses 0 whether its looping or not
void part2(const std::vector<Rotation>& rotations)
{
  ScopedTimer timer("Part 2");
  int total = 0;
  int dial = 50;
  for (const auto& r : rotations)
  {
    total += countZeroCrosses(dial, r); // add the times the Dial crosses 0 to the total
    dial = moveDial(dial, r);           // actually move the dial for the next count
  }
  printTotal(total);
}

std::vector<Rotation> parseInput(const std::vector<std::string>& lines)
{
  std::vector<Rotation> rotations;
 for (const auto& line : lines)
 {
   Rotation r;
   if (line[0] == 'L') r.d = -1;
   else r.d = 1;
   r.a = std::stoi(line.substr(1));
   rotations.push_back(r);
 }
 return rotations;
}

int main(int argc, char **argv)
{
  ScopedTimer timer("Main");
  int file = EXAMPLE_FILE; // default

  if (argc > 1) {
      try {
          file = std::stoi(argv[1]);
      } catch (...) {
          std::cerr << "Invalid file index, using EXAMPLE_FILE\n";
      }
  }

  InputData input = readFile(file);
  auto rotations = parseInput(input.lines);
  header(input);
  part1(rotations);
  part2(rotations);
  return 0;
}
