#include "../../helpers/getInput.hpp"

enum FileType { EXAMPLE_FILE, PUZZLE_FILE };

void part1(const InputData& input);
void part2(const InputData& input);
void printTotal(int total);

int main(int argc, char **argv)
{
    InputData input = readFile(EXAMPLE_FILE);
    header(input);
    part1(input);
    part2(input);
    return 0;
}

void printTotal(int total)
{
    static int calls = 1;
    printf("Part%i Total: %i\n", calls,total);
    calls++;
}
void part1(const InputData& input)
{
    int total = 0;
    printTotal(total);
}
void part2(const InputData& input)
{
    int total = 0;
    printTotal(total);
}
