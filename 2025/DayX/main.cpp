#include "../../helpers/getInput.hpp"

enum FileType { EXAMPLE_FILE, PUZZLE_FILE, CUSTOM_EXAMPLE_FILE };

void printTotal(long long total)
{
    static int calls = 1;
    printf("Part %i Answer: %lld\n", calls,total);
    calls++;
}

void part1(const InputData& input)
{
    Timer t;
    t.start();
    long long total = 0;
    for (const auto& line : input.lines)
    {
      printf("%s\n", line.c_str());
    }
    printTotal(total);
    t.stopAndPrint("Part 1");
}

void part2(const InputData& input)
{
    Timer t;
    t.start();
    long long total = 0;
    for (const auto& line : input.lines)
    {
      printf("%s\n", line.c_str());
    }
    printTotal(total);
    t.stopAndPrint("Part 2");
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
