#include "../../helpers/getInput.hpp"
#include "../../helpers/timer.hpp"
#include <set>
#include <map>
#include <tuple>

enum FileType { EXAMPLE_FILE, PUZZLE_FILE, CUSTOM_EXAMPLE_FILE };

void printTotal(long long total)
{
    static int calls = 1;
    printf("Part%i Answer: %lld\n", calls, total);
    calls++;
}

struct Beam { int row, col; };

// Part 1: count splits
int countSplits(const std::vector<std::string>& grid)
{
    int rows = grid.size();
    int cols = grid[0].size();

    int start_col = grid[0].find('S');
    std::vector<int> activeCols = {start_col};
    int splits = 0;

    for (int r = 1; r < rows; ++r)
    {
        std::set<int> nextCols;   // Beams for next row
        std::set<int> splitters;  // Unique splitters hit this row

        for (int c : activeCols)
        {
            char cell = grid[r][c];
            if (cell == '.') 
            {
                nextCols.insert(c);
            }
            else if (cell == '^') 
            {
                splitters.insert(c);
                if (c - 1 >= 0) nextCols.insert(c - 1);
                if (c + 1 < cols) nextCols.insert(c + 1);
            }
        }

        splits += splitters.size();       
        activeCols.assign(nextCols.begin(), nextCols.end());
    }

    return splits;
}

// Part 2: count quantum timelines recursively
long long countTimelines(int row, int col, const std::vector<std::string>& grid,
                         std::map<std::pair<int,int>, long long>& memo)
{
    int rows = grid.size();
    int cols = grid[0].size();

    // Out of bounds
    if (col < 0 || col >= cols) return 0;
    if (row >= rows) return 1; // reached bottom: one timeline

    std::pair<int,int> key = {row, col};
    if (memo.count(key)) return memo[key];

    char cell = grid[row][col];
    long long total = 0;

    if (cell == '.') {
        total = countTimelines(row + 1, col, grid, memo);
    } else if (cell == '^') {
        // split into left and right
        total = countTimelines(row + 1, col - 1, grid, memo) +
                countTimelines(row + 1, col + 1, grid, memo);
    }

    memo[key] = total;
    return total;
}

void part1(const InputData& input)
{
    Timer t;
    t.start();
    long long total = 0;
    total += countSplits(input.lines);
    printTotal(total);

    t.stopAndPrint("Part 1");
}

void part2(const InputData& input)
{
    Timer t;
    t.start();
    int start_col = input.lines[0].find('S');
    std::map<std::pair<int,int>, long long> memo;
    long long total = countTimelines(1, start_col, input.lines, memo); // start at row 1
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

