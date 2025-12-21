#include "../../helpers/getInput.hpp"

enum FileType { EXAMPLE_FILE, PUZZLE_FILE };

void printTotal(int total)
{
    static int calls = 1;
    printf("\nPart%i Total: %i\n", calls,total);
    calls++;
}

int moveDial(int current, char dir, int amount)
{
  if (dir == 'L')
    current -= amount;
  else if (dir == 'R')
    current += amount;

  //contain to 0-99
  current = (current % 100 + 100) % 100;

  return current;
}

int countZeroCrosses(int dial, char dir, int amount)
{
  int zeroCrosses = 0;
  // printf("Going %c for %d clicks from %d\n", dir, amount, dial);

  for (int i = 0; i < amount; ++i)
  {
    if (dir == 'R')
    {
      dial = (dial +1) %100;
    } else if (dir == 'L')
    {
      dial = (dial -1+100)%100;
    }
    // printf("%d\n", dial);
    if (dial == 0) zeroCrosses++;
  }
  // printf("Crossed Zero %d times.\n", zeroCrosses);
  return zeroCrosses;
}

//in part 1 we need to count he times the dial points at zero
void part1(const InputData& input)
{
  // We have a Safe Dial that has numbers 0-99 and starts pointing at 50
  int total = 0;
  int dial = 50;
  for (const auto& line : input.lines)
  {
    // Make sure we dont have a blank line
    if (line.empty()) continue;

    char dir = line[0];
    int amount = std::stoi(line.substr(1));
    dial = moveDial(dial, dir, amount);

    // printf("%d\n", dial);
    if (dial == 0) total ++;
  }
  printTotal(total);
}

//in part 2 we need to count the times the dial crosses 0 whether its looping or not
void part2(const InputData& input)
{
    int total = 0;
    int dial = 50;
    for (const auto& line : input.lines)
    {
      if(line.empty()) continue;

      char dir = line[0];
      int amount = std::stoi(line.substr(1));

      // add the times the Dial crosses 0 to the total
      total += countZeroCrosses(dial, dir, amount);

      // actually move the dial for the next count
      dial = moveDial(dial, dir, amount);
    }
    printTotal(total);
}

int main(int argc, char **argv)
{
    int file = EXAMPLE_FILE; // default

    if (argc > 1) {
        try {
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
