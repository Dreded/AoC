#include "helpers/getInput.hpp"

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
struct dimensions
{
    int l;
    int w;
    int h;
};

int findNeededPaper(dimensions present)
{
    const int arraySize = 3;
    int area[arraySize] = {
        2 * present.l * present.w,
        2 * present.w * present.h,
        2 * present.h * present.l};

    //sort the sides so we can get smallest from first array element
    for (int i = 0; i < arraySize; i++)
    {
        for (int j = i+1; j < arraySize; j++)
        {
            if (area[j] < area[i])
            {
                int temp = area[i];
                area[i] = area[j];
                area[j] = temp;
            }
        }
    }

    return (area[0] + area[1] + area[2] + area[0]/2);
}

int findNeededRibbon(dimensions present)
{
    const int arraySize = 3;
    int sides[arraySize] = {present.l,present.w,present.h};

    //sort the sides so we can get smallest 2 from first/second array element
    for (int i = 0; i < arraySize; i++)
    {
        for (int j = i+1; j < arraySize; j++)
        {
            if (sides[j] < sides[i])
            {
                int temp = sides[i];
                sides[i] = sides[j];
                sides[j] = temp;
            }
        }
    }

    int two_smallest_sides = (2 * sides[0]) + (2 * sides[1]);
    int volume = (sides[0] * sides[1] * sides[2]);

    return two_smallest_sides + volume;
}
void part1(std::vector<std::string> lines)
{
    int total = 0;
    for (std::string &line : lines)
    {
        dimensions present;
        std::sscanf(line.c_str(), "%ix%ix%i", &present.l, &present.w, &present.h);
        total += findNeededPaper(present);
    }
    printTotal(total);
}
void part2(std::vector<std::string> lines)
{
    int total = 0;
    for (std::string &line : lines)
    {
        dimensions present;
        std::sscanf(line.c_str(), "%ix%ix%i", &present.l, &present.w, &present.h);
        total += findNeededRibbon(present);
    }
    printTotal(total);
}