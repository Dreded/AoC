#include "helpers/getInput.hpp"
#include <filesystem>

void part1(std::vector<std::string> lines)
{
    int elfNum = 0;
    int currentCount = 0;
    int largestCalories = 0;
    int largestElf = 0;
    for (std::string line : lines)
    {
        // std::cout << line << std::endl;
        if (line.length() > 0)
        {
            currentCount += std::stoi(line);
            if (currentCount > largestCalories)
            {
                largestElf = elfNum;
                largestCalories = currentCount;
            }
        }
        else
        {
            // std::cout << "Elf" << elfNum+1 << ": " << currentCount << std::endl;
            elfNum++;
            currentCount = 0;
        }
    }
    std::cout << "Elf" << largestElf + 1 << ": " << largestCalories << std::endl;
}
void part2(std::vector<std::string> lines)
{
    int elfNum = 0;
    int currentCount = 0;
    int largestCalories[3] = {0};

    for (int i = 0; i < lines.size(); i++)
    {
        std::string line = lines[i];
        // std::cout << line << std::endl;
        if (line.length() > 0)
        {
            currentCount += std::stoi(line);
        }
        else
        {
            if (currentCount > largestCalories[0])
            {
                largestCalories[2] = largestCalories[1];
                largestCalories[1] = largestCalories[0];
                largestCalories[0] = currentCount;
            }
            else if (currentCount > largestCalories[1])
            {
                largestCalories[2] = largestCalories[1];
                largestCalories[1] = currentCount;
            }
            else if (currentCount > largestCalories[2])
            {
                largestCalories[2] = currentCount;
            }
            // std::cout << "Elf" << elfNum+1 << ": " << currentCount << std::endl;
            elfNum++;
            currentCount = 0;
        }
    }
    // We need to add in the last output if neccesary(it is on demo but not in problem)
    if (currentCount > largestCalories[0])
    {
        largestCalories[2] = largestCalories[1];
        largestCalories[1] = largestCalories[0];
        largestCalories[0] = currentCount;
    }
    else if (currentCount > largestCalories[1])
    {
        largestCalories[2] = largestCalories[1];
        largestCalories[1] = currentCount;
    }
    else if (currentCount > largestCalories[2])
    {
        largestCalories[2] = currentCount;
    }
    std::cout << largestCalories[0] << " : " << largestCalories[1] << " : " << largestCalories[2] << std::endl;
    std::cout << "Total: " << largestCalories[0] + largestCalories[1] + largestCalories[2] << std::endl;
}

int main(int argc, char **argv)
{
    const std::filesystem::path exePath = std::filesystem::path(argv[0]).parent_path();
    std::vector<std::string> lines = readFile(exePath, 0);
    part1(lines);
    part2(lines);
    return 0;
}
