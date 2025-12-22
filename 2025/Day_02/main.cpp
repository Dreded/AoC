#include "../../helpers/getInput.hpp"
#include <sstream>

enum FileType { EXAMPLE_FILE, PUZZLE_FILE, CUSTOM_EXAMPLE_FILE };

void printTotal(long long total)
{
    static int calls = 1;
    printf("Part%i Total: %lld\n", calls,total);
    calls++;
}

long long rangeCheckHalf(const long long& start, const long long& end)
{
  long long total = 0;

  for (long long i = start; i <= end; i++)
  {
    std::string s = std::to_string(i);
    int len  = s.size();

    // if the string length is odd its valid so skip this loop
    if (len % 2 != 0) continue;
    int half = len/2;
    if (s.substr(0,half) == s.substr(half,half))
    {
      // its repeating/invalid
      total += i;
    }
  }
  return total;
}

long long rangeCheckAll(const long long& start, const long long& end)
{
  long long total = 0;
  
  for (long long i = start; i <= end; i++)
  {
    std::string s = std::to_string(i);
    int len  = s.size();
    // we need to check every sub sequence up to Half the length(2)
    for (int seqLen = 1; seqLen <= len/2; seqLen++)
    {
      if (len % seqLen != 0) continue; // skip if not evenly divisible int X sequence
      std::string seq = s.substr(0,seqLen);
      std::string repeated;

      //simply take the first X characters and repeat it Y times and check for a match
      for (int j = 0; j < len/seqLen; j++)
        repeated += seq;
      if (repeated == s)
      {
        total += i;
        break;
      }
    }
  }
  return total;
}

long long rangeCheck(const std::string& range, int part)
{
  long long total = 0;
  long long start, end;
  char dash;
  std::stringstream ss(range);
  ss >> start >> dash >> end;

  if (part == 1) total = rangeCheckHalf(start, end);
  if (part == 2) total = rangeCheckAll(start, end);

  return total;
}

std::vector<std::string> splitLine(const std::string& line)
{
  std::vector<std::string> ranges;
  std::stringstream ss(line);
  std::string token;

  while (std::getline(ss, token, ',')) //split by comma
  {
    ranges.push_back(token);
  }
  
  return ranges;
}

void part1(const std::vector<std::string>& ranges)
{
  long long total = 0;
  for (const std::string& r : ranges)
  {
    total += rangeCheck(r,1);
  }

  printTotal(total);
}

void part2(const std::vector<std::string>& ranges)
{
    long long total = 0;
  for (const std::string& r : ranges)
  {
    total += rangeCheck(r,2);
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
    auto ranges = splitLine(input.lines[0]);
    
    header(input);
    printf("Total Ranges Found: %ld\n", ranges.size());
    part1(ranges);
    part2(ranges);
    return 0;
}
