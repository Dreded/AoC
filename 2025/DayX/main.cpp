#include "../../helpers/getInput.hpp"

enum FileType { EXAMPLE_FILE, PUZZLE_FILE, CUSTOM_EXAMPLE_FILE };

void printTotal(long long total)
{
    static int calls = 1;
    printf("Part%i Answer: %lld\n", calls,total);
    calls++;
}
void part1(const InputData& input)
{
    long long total = 0;
    printTotal(total);
}
void part2(const InputData& input)
{
    long long total = 0;
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
