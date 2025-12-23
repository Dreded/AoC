#include "../../helpers/getInput.hpp"
#include "../../helpers/timer.hpp"
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <set>
#include <climits>

enum FileType { EXAMPLE_FILE, PUZZLE_FILE, CUSTOM_EXAMPLE_FILE };

void printTotal(long long total)
{
  static int calls = 1;
  printf("Part %i Answer: %lld\n", calls,total);
  calls++;
}

struct Point
{
  int x,y;
};

long long calcArea(const Point& a, const Point& b)
{
  long long width = std::abs(a.x - b.x) + 1;
  long long height = std::abs(a.y - b.y) + 1;

  return width * height;
}

long long findMaxArea(const std::vector<Point>& points)
{
  long long max = 0;
  for (size_t i = 0; i < points.size(); ++i)
    for (size_t j = i+1; j < points.size(); ++j)
        max = std::max(max, calcArea(points[i], points[j]));
  return max;
}

// in part 1 we just need to find the largest rectangle(area) between any two points
void part1(const std::vector<Point>& points)
{
  ScopedTimer timer("Part 1");
  long long total = findMaxArea(points);
  printTotal(total);
}
// Each row maps to a vector of intervals [startX, endX] that are valid (# or X)
using RowIntervals = std::unordered_map<int, std::vector<std::pair<int,int>>>;

void drawLines(RowIntervals& rows, const std::vector<Point>& points)
{
    int n = points.size();
    for (int i = 0; i < n; ++i)
    {
        const Point& a = points[i];
        const Point& b = points[(i+1)%n];

        if (a.y == b.y)
        {
            // horizontal line
            int x1 = std::min(a.x,b.x);
            int x2 = std::max(a.x,b.x);
            rows[a.y].push_back(std::make_pair(x1,x2));
        }
        else
        {
            // vertical line
            int y1 = std::min(a.y,b.y);
            int y2 = std::max(a.y,b.y);
            for (int y = y1; y <= y2; ++y)
                rows[y].push_back(std::make_pair(a.x,a.x));
        }
    }

    // merge intervals per row
    for (auto& row : rows)
    {
        std::vector<std::pair<int,int>>& vec = row.second;
        std::sort(vec.begin(), vec.end());
        std::vector<std::pair<int,int>> merged;
        for (auto& interval : vec)
        {
            if (!merged.empty() && interval.first <= merged.back().second + 1)
                merged.back().second = std::max(merged.back().second, interval.second);
            else
                merged.push_back(interval);
        }
        vec = std::move(merged);
    }
}

void fillInterior(RowIntervals& rows)
{
    // Find min/max y
    int minY = INT_MAX, maxY = INT_MIN;
    for (auto& row : rows) { minY = std::min(minY, row.first); maxY = std::max(maxY, row.first); }

    for (int y = minY; y <= maxY; ++y)
    {
        auto it = rows.find(y);
        if (it == rows.end() || it->second.size() < 2) continue;

        // fill gaps between intervals
        std::vector<std::pair<int,int>> newIntervals;
        int lastEnd = it->second[0].second;
        for (size_t i = 1; i < it->second.size(); ++i)
        {
            int s = it->second[i].first;
            if (s > lastEnd + 1)
                newIntervals.push_back(std::make_pair(lastEnd+1, s-1)); // interior
            lastEnd = it->second[i].second;
        }

        it->second.insert(it->second.end(), newIntervals.begin(), newIntervals.end());
        std::sort(it->second.begin(), it->second.end());

        // merge again
        std::vector<std::pair<int,int>> merged;
        for (auto& interval : it->second)
        {
            if (!merged.empty() && interval.first <= merged.back().second + 1)
                merged.back().second = std::max(merged.back().second, interval.second);
            else
                merged.push_back(interval);
        }
        it->second = std::move(merged);
    }
}

bool isValidRectangle(const RowIntervals& rows, const Point& p1, const Point& p2)
{
    int x1 = std::min(p1.x, p2.x);
    int x2 = std::max(p1.x, p2.x);
    int y1 = std::min(p1.y, p2.y);
    int y2 = std::max(p1.y, p2.y);

    for (int y = y1; y <= y2; ++y)
    {
        auto it = rows.find(y);
        if (it == rows.end()) return false;

        bool rowValid = false;
        for (auto& interval : it->second)
        {
            if (interval.first <= x1 && interval.second >= x2)
            {
                rowValid = true;
                break;
            }
        }
        if (!rowValid) return false;
    }
    return true;
}

long long findLargestRectangle(const RowIntervals& rows, const std::vector<Point>& points)
{
    long long maxArea = 0;
    for (size_t i = 0; i < points.size(); ++i)
    {
        for (size_t j = i+1; j < points.size(); ++j)
        {
            if (!isValidRectangle(rows, points[i], points[j])) continue;

            long long area = (long long)(std::abs(points[i].x - points[j].x) + 1) *
                             (long long)(std::abs(points[i].y - points[j].y) + 1);
            if (area > maxArea) maxArea = area;
        }
    }
    return maxArea;
}

// now the points make a outline and we connect each one with a straight line
// find the largest rectangle inside this outline
// we will construct the grid, then do a scanline fill to fill it.. which crashed the computer
// so now we need to do this without creating the 10GB grid
void part2(const std::vector<Point>& points)
{
  ScopedTimer timer("Part 2");
  RowIntervals rows;
  drawLines(rows, points);
  fillInterior(rows);
  long long total = findLargestRectangle(rows, points);
  printTotal(total);
}

std::vector<Point> parsePoints(const std::vector<std::string>& lines)
{
  std::vector<Point> points;
  for (auto& line : lines)
  {
    std::stringstream ss(line);
    Point p;
    char c1;
    if (ss >> p.x >> c1 >> p.y && c1 == ',')
    {
      points.push_back(p);
    } else {
      std::cerr << "Skipping malformed line: " << line << "\n";
    }
  }
  return points;
}

int main(int argc, char **argv)
{
  ScopedTimer timer("Main");
  int file = EXAMPLE_FILE; // default

  if (argc > 1)
  {
    try
    {
      file = std::stoi(argv[1]);
    } catch (...) {
      std::cerr << "Invalid file index, using EXAMPLE_FILE\n";
    }
  }

  InputData input = readFile(file);
  auto points = parsePoints(input.lines);
  header(input);
  part1(points);
  part2(points);
  return 0;
}
