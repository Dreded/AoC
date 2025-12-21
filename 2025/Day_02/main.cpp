#include "../../helpers/getInput.hpp"
#include <sstream>

enum FileType { EXAMPLE_FILE, PUZZLE_FILE, CUSTOM_EXAMPLE_FILE };

void printTotal(long long total)
{
    static int calls = 1;
    printf("Part%i Total: %lld\n", calls,total);
    calls++;
}
long long rangeCheck(const std::string& range)
{
  long long total = 0;
  std:: stringstream ss(range);
  long long start, end;
  char dash;
  ss >> start >> dash >> end;
  // printf("Start: %d\t End: %d\n", start, end);

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

void part1(const InputData& input)
{
  long long total = 0;
  auto ranges = splitLine(input.lines[0]);
  printf("Total Ranges Found: %ld\n", ranges.size());
  for (const std::string& r : ranges)
  {
    total += rangeCheck(r);
  }

  printTotal(total);
}

void part2(const InputData& input)
{
    int total = 0;
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
