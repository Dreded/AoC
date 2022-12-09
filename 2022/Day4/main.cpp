#include "helpers/getInput.hpp"
#include <utility> // for std::pair

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
    printf("Part%i Total: %i\n", calls,total);
    calls++;
}

//This is a mess don't use it, we re-did it for part 2
std::string splitStrings[2];
void splitString(std::string &line, char delim)
{
    // Create a stringstream from the input string.
    std::stringstream ss(line);

    // Use std::getline to split the string at the comma character.
    std::string item;

    //split string at first delimeter only
    for (int i = 0; i < 2; i++)
    {
        std::getline(ss, item, delim);
        splitStrings[i] = item;
    }
    //std::cout << splitStrings[0] << " : " << splitStrings[1] << std::endl;
}
bool fullyContained(int elfs[2][2])
{
    if (elfs[0][0] <= elfs[1][0] && elfs[0][1] >= elfs[1][1])
        return true;
    else if (elfs[1][0] <= elfs[0][0] && elfs[1][1] >= elfs[0][1])
        return true;
    
    return false;
}
void part1(std::vector<std::string> lines)
{
    int total = 0;
    int elfs[2][2] = {0};

    for (std::string line : lines)
    {
        splitString(line, ',');
        std::string holder[2] = {splitStrings[0], splitStrings[1]};
        for(int j = 0;j < 2; j++)
        {
            splitString(holder[j], '-');
            elfs[j][0] = std::stoi(splitStrings[0]);
            elfs[j][1] = std::stoi(splitStrings[1]);
        }
        total += fullyContained(elfs);
        //printf("Elf1=%i:%i, Elf2=%i:%i\n",elfs[0][0], elfs[0][1], elfs[1][0], elfs[1][1] );
    }
    printTotal(total);
}

//Part2 Much cleaner.
struct Range
{
    int start;
    int end;
};
bool rangesOverlap(Range first, Range second)
{
    //We are checking if the first range is completely to the right of the second range.
    if (first.end < second.start)
        return false;

    // is it compeltely to the left?
    if (first.start > second.end)
        return false;

    //must overlap then
    return true;
}
void part2(std::vector<std::string> lines)
{
    //ok we need a compelte re-write... learning :)
    int total = 0;
    for(std::string line : lines)
    {
        Range _range1;
        Range _range2;
        std::sscanf(line.c_str(),"%d-%d,%d-%d", &_range1.start, &_range1.end, &_range2.start, &_range2.end);
        total += rangesOverlap(_range1,_range2);
    }
    printTotal(total);
}