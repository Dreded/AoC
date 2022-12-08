#include "helpers/getInput.hpp"

#define EXAMPLE_FILE 0
#define PUZZLE_FILE 1

void part1(std::vector<std::string> lines);
void part2(std::vector<std::string> lines);

int main(int argc, char **argv)
{
    std::vector<std::string> lines = readFile(PUZZLE_FILE);
    part1(lines);
    part2(lines);
    return 0;
}

void part1(std::vector<std::string> lines)
{
    int total = 0;
    for(std::string line : lines)
    {
        std::string compartment1 = line.substr(0,line.length()/2);
        std::string compartment2 = line.substr(line.length()/2);
        for(char c : compartment1)
        {
            if(compartment2.find_first_of(c) < std::string::npos)
            {
                int ammount = 64-26;
                if(c > 96) ammount = 96;
                total += c - ammount;
                break;
            }
        }
    }
    std::cout << "Part1: " << total << std::endl;
}
void part2(std::vector<std::string> lines)
{
}