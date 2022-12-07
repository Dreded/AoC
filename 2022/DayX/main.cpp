#include "helpers/getInput.hpp"
#include <filesystem>
void part1(std::vector<std::string> lines);
void part2_no_sort(std::vector<std::string> lines);
void findTop3(int &currentCount, int largestCalories[3]);

int main(int argc, char **argv)
{
    const std::filesystem::path exePath = std::filesystem::path(argv[0]).parent_path();
    std::vector<std::string> lines = readFile(exePath, 1);
    part1(lines);
    part2_no_sort(lines);
    return 0;
}

void part1(std::vector<std::string> lines)
{
}
void part2_no_sort(std::vector<std::string> lines)
{

}