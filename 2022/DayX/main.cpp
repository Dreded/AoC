#include "helpers/getInput.hpp"

#define EXAMPLE_FILE 0
#define PUZZLE_FILE 1

void part1(std::vector<std::string> lines);
void part2(std::vector<std::string> lines);
void printTotal(int total);

int main(int argc, char **argv)
{
    std::vector<std::string> lines = readFile(EXAMPLE_FILE);
    part1(lines);
    part2(lines);
    return 0;
}

void printTotal(int total)
{
    static int calls = 1;
    printf("Part%i Total: %i\n", calls,total);
    calls++;
}

void part1(std::vector<std::string> lines)
{
    int total = 0;
    printTotal(total);
}
void part2(std::vector<std::string> lines)
{
    int total = 0;
    printTotal(total);
}