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

void printAnswer(std::vector<std::vector<char>> &stacks)
{
    static int calls = 1;
    printf("Part%i Answer: ", calls);
    for (auto &stack : stacks)
    {
        printf("%c", stack.back());
    }
    printf("\n");
    calls++;
}

void printStacks(std::vector<std::vector<char>> &stacks)
{
    for (const auto &stack : stacks)
    {
        for (char c : stack)
        {
            std::cout << "[" << c << "] ";
        }
        std::cout << std::endl;
    }
}

struct moveSet
{
    int num;
    int from;
    int to;
};

void parseStacks(std::vector<std::vector<char>> &stacks, const std::string &line, int &total_stacks)
{
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

moveSet parseMoves(std::vector<std::vector<char>> &stacks, const std::string &line)
{
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
    moveSet m;
    ss >> word >> m.num >> word >> m.from >> word >> m.to;

    // indexing from 0
    m.from--;
    m.to--;

    return m;
}

void part1(std::vector<std::string> lines)
{
    // Calculate the number of stacks 4 = number of characters per stack
    int total_stacks = lines.front().length() / 4 + 1;

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
            parseStacks(stacks, line, total_stacks);
        }
        else
        {

            // Parse the moves section
            moveSet m = parseMoves(stacks, line);

            // Perform the move
            for (int i = 0; i < m.num; i++)
            {
                stacks[m.to].push_back(stacks[m.from].back());
                stacks[m.from].pop_back();
            }
        }
    }

    // Print the final stacks
    // printStacks(stacks);
    printAnswer(stacks);
}

void part2(std::vector<std::string> lines)
{ // Calculate the number of stacks 4 = number of characters per stack
    int total_stacks = lines.front().length() / 4 + 1;

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
            parseStacks(stacks, line, total_stacks);
        }
        else
        {
            // Parse the moves section 
            //or some reason this is different than the above parseMoves... I dont get it.
            //moveSet m = parseMoves(stacks,line); // doesnt work
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
            moveSet m;
            ss >> word >> m.num >> word >> m.from >> word >> m.to;
            m.from--;
            m.to--;

            // Perform the move
            std::vector<char> currentMove;
            for (int i = 0; i < m.num; i++)
            {
                currentMove.push_back(stacks[m.from].back());
                stacks[m.from].pop_back();
            }
            std::reverse(currentMove.begin(), currentMove.end());
            stacks[m.to].insert(stacks[m.to].end(), currentMove.begin(), currentMove.end());
        }
    }

    // Print the final stacks
    printStacks(stacks);
    printAnswer(stacks);
}