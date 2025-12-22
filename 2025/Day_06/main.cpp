#include "../../helpers/getInput.hpp"

enum FileType { EXAMPLE_FILE, PUZZLE_FILE, CUSTOM_EXAMPLE_FILE };

void printTotal(long long total)
{
    static int calls = 1;
    printf("Part%i Answer: %lld\n", calls,total);
    calls++;
}

const std::vector<std::vector<long long>> getNums(const std::vector<std::string>& lines)
{
  int lastLine = lines.size() - 1;
  std::vector<std::vector<long long>> nums;

  //skip trailing blank lines
  while (lastLine >= 0 && lines[lastLine].empty())
    --lastLine;

  //last non empty line is the operators so stop before
  for (int i = 0; i < lastLine ; ++i)
  {
    std::stringstream ss(lines[i]);
    std::vector<long long> row;

    long long value;
    while(ss>>value) //skips whitespace automagically
      row.push_back(value);

    if(!row.empty())
      nums.push_back(row);
  }

  return nums;
}

const std::vector<char> getOperators(const std::vector<std::string>& lines)
{
  std::vector<char> operators;
  for(auto i = lines.rbegin(); i != lines.rend(); ++i)
  {
    //find last non empty line
    if (i->empty()) continue;

    for (char c : *i)
    {
      if (c == '+' || c == '*')
        operators.push_back(c);
    }
    break;
  }

  return operators;
}

long long doMath(const std::vector<std::vector<long long>>& nums, const std::vector<char>& operators)
{
  long long total = 0;
  int cols = operators.size();
  for (int i = 0; i < cols; ++i)
  {
    char op = operators[i];
    long long colTotal = 0;
    // dont multiply by zero
    if (op == '*') colTotal = 1;
    for (auto& row : nums)
    {
      if (op == '*') colTotal *= row[i];
      else if (op == '+') colTotal += row[i];
    }
    total += colTotal;
  }
  return total;
}

void part1(const InputData& input)
{
    long long total = 0;
    const auto operators = getOperators(input.lines);
    const auto nums = getNums(input.lines);

    total += doMath(nums, operators);

    printTotal(total);
}

std::vector<std::string> transpose(const std::vector<std::string>& lines)
{
  if (lines.empty()) return {};

  size_t rows = lines.size();
  size_t cols = lines[0].size();

  std::vector<std::string> result(cols, std::string(rows, ' '));
  
  for (size_t r = 0; r < rows; ++r)
    for (size_t c = 0; c < cols; ++c)
    {
      result[c][r] = lines[r][c]; //flip row/column
    }

  return result;
}

// check if a line is blank.. any non white space means its not blank
bool isBlank(const std::string& line)
{
  for (char c : line)
    if (!isspace(c)) return false;
  return true;
}
// ok in part2 suddenly white space matters... so to make it not matter we will transpose the data
void part2(const InputData& input)
{
    long long total = 0;
    const auto operators = getOperators(input.lines);

    //copy the input and remove the last line(operators)
    std::vector<std::string> lines = input.lines;
    lines.pop_back();
    auto transposedLines = transpose(lines);

    size_t rowIndex = 0;
    int operatorIndex = 0;
    while (rowIndex < transposedLines.size())
    {
      char op = operators[operatorIndex];
      long long thisTotal = 0;
      if (op == '*') thisTotal = 1;

      while (rowIndex < transposedLines.size() && !isBlank(transposedLines[rowIndex]))
      {
        long long num = std::stoll(transposedLines[rowIndex]);
        if (op == '+') thisTotal += num;
        if (op == '*') thisTotal *= num;
        rowIndex++;
      }
      total += thisTotal;
      rowIndex++; //skip blank line
      operatorIndex++; //we hit a blank so use the next operator
    }
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
