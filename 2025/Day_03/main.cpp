#include "../../helpers/getInput.hpp"

enum FileType { EXAMPLE_FILE, PUZZLE_FILE, CUSTOM_EXAMPLE_FILE };

void printTotal(long long total)
{
    static int calls = 1;
    printf("Part%i Answer: %lld\n", calls,total);
    calls++;
}

int findLargestTwo(const std::string& line)
{
  int largest = 0;
  int len = line.size();
  
  for(int i = 0; i< len; ++i)
  {
    // only check digits after current pos for ones column
    for (int j = i+1; j < len; ++j)
    {
      // move first digit into the 10's column then add second num
      int num = (line[i]-'0')*10 + (line[j]-'0');
      if (num > largest) largest = num;
    }
  }

  return largest;
}

long long vectorToNumber(const std::vector<int>& digits)
{
  long long num = 0;
  for(int d : digits)
  {
    num = num*10+d; //shift all digits left and add current to 1s
  }
  return num;
}

long long findLargestN(const std::string& line, int length)
{
  std::vector<int> digits;
  int n = line.size();

  for (int i = 0; i < n; ++i)
  {
    int current = line[i] - '0';

    while (!digits.empty() && current > digits.back() && digits.size()-1+(n-i)>= length)
    {
      digits.pop_back();
    }

    if (digits.size() < length)
    {
      digits.push_back(current);
    }
  }

  long long num = vectorToNumber(digits);
  // printf("%0*lld\n",length, num);
  return num;
}

// given a sequence of numbers find the largest two in order and add them to total
void part1(const InputData& input)
{
    long long total = 0;
    for (const auto& line : input.lines)
    {
      if (line.empty()) continue;
      total += findLargestTwo(line);
    }
    printTotal(total);
}

// we now need to keep the largest 12 in order
// decided to make this work on any N digits so it will get part1 answer too
void part2(const InputData& input)
{
    long long total = 0;
    for (const auto& line : input.lines)
    {
      if (line.empty()) continue;
      total += findLargestN(line,12);
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
