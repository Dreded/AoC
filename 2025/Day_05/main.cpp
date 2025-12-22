#include "../../helpers/getInput.hpp"
#include <algorithm>
enum FileType { EXAMPLE_FILE, PUZZLE_FILE, CUSTOM_EXAMPLE_FILE };

void printTotal(long long total)
{
    static int calls = 1;
    printf("Part%i Answer: %lld\n", calls,total);
    calls++;
}

struct Range { long long start, end; };

std::vector<Range> mergeRanges(std::vector<Range> ranges)
{
  if (ranges.empty()) return {};
  std::sort(ranges.begin(), ranges.end(), [](auto& a, auto& b) { return a.start < b.start; });
  std::vector<Range> merged = {ranges[0]};
  for (size_t i = 1; i < ranges.size(); ++i)
  {
    if (ranges[i].start <= merged.back().end)
    {
      merged.back().end = std::max(merged.back().end, ranges[i].end);
    } else
    {
      merged.push_back(ranges[i]);
    }
  }
  return merged;
}

bool inAnyRange( const std::vector<Range>& ranges, long long num)
{
  for (const auto& r : ranges)
    if (num >= r.start && num <= r.end) return true;

  return false;
}

void part1(const InputData& input)
{
    long long total = 0;
    std::vector<Range> ranges;
    std::vector<long long> nums;

    for (const auto& line : input.lines)
    {
      if (line.empty()) continue; // skip blanks
      auto dashPos = line.find('-');
      if (dashPos != std::string::npos)
      {
        long long start = std::stoll(line.substr(0,dashPos));
        long long end = std::stoll(line.substr(dashPos+1));
        ranges.push_back({start, end});
      } else
      {
        nums.push_back(std::stoll(line));
      }
    }
    ranges = mergeRanges(ranges);
    for (auto& n : nums)
      total += inAnyRange(ranges, n);
    printTotal(total);
}

void part2(const InputData& input)
{
    long long total = 0;
    std::vector<Range> ranges;

    for (const auto& line : input.lines)
    {
      if (line.empty()) continue; // skip blanks
      auto dashPos = line.find('-');
      if (dashPos != std::string::npos)
      {
        long long start = std::stoll(line.substr(0,dashPos));
        long long end = std::stoll(line.substr(dashPos+1));
        ranges.push_back({start, end});
      }
    }
    ranges = mergeRanges(ranges);
    for (auto& r : ranges)
      total += r.end - r.start + 1;
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
