#include "helpers/getInput.hpp"
#include <algorithm>

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

void part1(std::vector<std::string> lines)
{
    // Calculate the number of stacks 4 = number of characters per stack
    int total_stacks = lines.front().length() / 4+1;

    // Create a vector of stacks
    std::vector<std::vector<char>> stacks(total_stacks);

    // Parse the input lines and extract the stacks and moves
    bool in_the_stacks = true;
    for (const std::string &line : lines)
    {
        if (line.empty())
        {
            // An empty line indicates the end of the stacks section
            in_the_stacks = false;
            continue;
        }

        if (in_the_stacks)
        {
            // Parse the stacks section
            const char *c_line = line.c_str();
            for (int i = 0; i < total_stacks; i++)
            {
                // Extract the character at the ith stack
                char c = c_line[(i * 4) + 1];
                if (c != ' ' && c > 60)
                {
                    // Push the character onto the ith stack if it is not a space and has an ASCII value greater than 60
                    stacks[i].push_back(c);
                }
            }
        }
        else
        {
            // Parse the moves section
            static bool do_once = true;
            if (do_once)
            {
                // Reverse the stacks
                for (auto &stack : stacks)
                {
                    std::reverse(stack.begin(), stack.end());
                }
                do_once = false;
            }

            // Extract the move parameters from the line
            std::istringstream ss(line);
            std::string word;
            int num;
            int from;
            int to;
            ss >> word >> num >> word >> from >> word >> to;

            // Perform the move
            for (int i = 0; i < num; i++)
            {
                stacks[to - 1].push_back(stacks[from - 1].back());
                stacks[from - 1].pop_back();
            }
        }
    }

    // // Print the final stacks
    // for (const auto &stack : stacks)
    // {
    //     for (char c : stack)
    //     {
    //         std::cout << "[" << c << "] ";
    //     }
    //     std::cout << std::endl;
    // }

    printf("Part1 Answer: ");
    for (auto &stack : stacks)
    {
        printf("%c", stack.back());
    }
    printf("\n");
}

void part2(std::vector<std::string> lines)
{   // Calculate the number of stacks 4 = number of characters per stack
    int total_stacks = lines.front().length() / 4+1;

    // Create a vector of stacks
    std::vector<std::vector<char>> stacks(total_stacks);

    // Parse the input lines and extract the stacks and moves
    bool in_the_stacks = true;
    for (const std::string &line : lines)
    {
        if (line.empty())
        {
            // An empty line indicates the end of the stacks section
            in_the_stacks = false;
            continue;
        }

        if (in_the_stacks)
        {
            // Parse the stacks section
            const char *c_line = line.c_str();
            for (int i = 0; i < total_stacks; i++)
            {
                // Extract the character at the ith stack
                char c = c_line[(i * 4) + 1];
                if (c != ' ' && c > 60)
                {
                    // Push the character onto the ith stack if it is not a space and has an ASCII value greater than 60
                    stacks[i].push_back(c);
                }
            }
        }
        else
        {
            // Parse the moves section
            static bool do_once = true;
            if (do_once)
            {
                // Reverse the stacks
                for (auto &stack : stacks)
                {
                    std::reverse(stack.begin(), stack.end());
                }
                do_once = false;
            }

            // Extract the move parameters from the line
            std::istringstream ss(line);
            std::string word;
            int num;
            int from;
            int to;
            ss >> word >> num >> word >> from >> word >> to;

            // Perform the move
            std::vector<char> currentMove;
            for (int i = 0; i < num; i++)
            {
                currentMove.push_back(stacks[from - 1].back());
                stacks[from - 1].pop_back();
            }
            std::reverse(currentMove.begin(), currentMove.end());
            stacks[to-1].insert(stacks[to-1].end(), currentMove.begin(),currentMove.end());
        }
    }

    // Print the final stacks
    for (const auto &stack : stacks)
    {
        for (char c : stack)
        {
            std::cout << "[" << c << "] ";
        }
        std::cout << std::endl;
    }

    printf("Part2 Answer: ");
    for (auto &stack : stacks)
    {
        printf("%c", stack.back());
    }
    printf("\n");
}