#include "../../helpers/getInput.hpp"

enum FileType { EXAMPLE_FILE, PUZZLE_FILE, CUSTOM_EXAMPLE_FILE };

void printTotal(long long total)
{
    static int calls = 1;
    printf("Part%i Answer: %lld\n", calls,total);
    calls++;
}

int checkGrid(const std::vector<std::string>& gridInput, bool clearGrid = false)
{
  // make a copy of the grid so we can modify it.
  std::vector<std::string> grid = gridInput;

  int accessible = 0;
  int rows = grid.size();
  int cols = grid[0].size();
  // printf("Rows: %d\t Cols: %d\n", rows, cols);
  // Directions Row/Col for 8 Neighbours: N, NE, E, SE, S,SW, W,Answer
  std::vector<std::pair<int,int>> neighbours {
    {-1,-1}, {-1,0}, {-1,1},
     {0,-1},          {0,1},
     {1,-1},  {1,0},  {1,1}
  };
  // int dr[] = {-1,-1,0,1,1,1,0,-1};
  // int dc[] = {0,1,1,1,0,-1,-1,-1};
  bool loopAgain = true;
  while(loopAgain)
  {
    loopAgain = false;
    for (int r = 0; r < rows; ++r)
    {
      for (int c = 0; c < cols; ++c)
      {
        // if theres NOT a roll of paper at this position skip the work
        if (grid[r][c] != '@') continue;
        int neighbourCount = 0;

        for (auto& n : neighbours)
        {
          // check all neighbours
          int nr = r + n.first;
          int nc = c + n.second;
          //make sure its inbounds
          if (nr >= 0 && nr < rows && nc >= 0 && nc < cols)
            if (grid[nr][nc] == '@') neighbourCount++;
        }
        if (neighbourCount < 4)
        {
          accessible++;
          // should the forklift dude take it away?
          if (clearGrid)
          {
            grid[r][c] = '.';
            // we took one away so Loop again to clear as many as we can
            loopAgain = true;
          }
        }
      }
    }
  }
  return accessible;
}

void part1(const InputData& input)
{
    long long total = 0;
    const auto& grid = input.lines;
    total = checkGrid(grid);

    printTotal(total);
}

void part2(const InputData& input)
{
    long long total = 0;
    const auto& grid = input.lines;
    bool clearGrid = true;
    total = checkGrid(grid, clearGrid);
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
