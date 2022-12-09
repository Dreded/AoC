#include "helpers/getInput.hpp"
#include <unordered_set>

#define EXAMPLE_FILE 0
#define PUZZLE_FILE 1

void part1(std::vector<std::string> lines);
void part2(std::vector<std::string> lines);
void printTotal(int total);

int main(int argc, char **argv)
{
    std::vector<std::string> lines = readFile(PUZZLE_FILE);
    part1(lines);
    part2(lines);
    return 0;
}

void printTotal(int total)
{
    static int calls = 1;
    printf("Part%i Total: %i\n", calls, total);
    calls++;
}

int getMarker(int unique_in_row, const std::string &line)
{

    // Create an unordered set to keep track of unique characters
    std::unordered_set<char> uniqueChars;
    for (int i = 0; i < line.length(); i++)
    {
        for (int j = 0; j < unique_in_row; ++j)
        {
            char c = line[i + j];
            if (!uniqueChars.count(c))
            {
                uniqueChars.insert(c);
            }
        }
        if (uniqueChars.size() == unique_in_row)
        {
            return i + unique_in_row;
        }
        uniqueChars.clear();
    }
}

void part1(std::vector<std::string> lines)
{
    int total = 0;
    std::string line = lines.front();

    total += getMarker(4, line);
    printTotal(total);
}
void part2(std::vector<std::string> lines)
{
    int total = 0;
    std::string line = lines.front();

    total += getMarker(14, line);
    printTotal(total);
}