#include <iostream>
#include <fstream>
#include <string>

//solution to part2

// Represents a range of numbers
struct Range {
  int start;
  int end;
};

// Represents a pair of ranges
struct RangePair {
  Range first;
  Range second;
};

// Determines if the given ranges overlap
bool rangesOverlap(Range first, Range second) {
  // Check if the first range is completely to the right of the second range
  if (first.end < second.start) {
    return false;
  }

  // Check if the first range is completely to the left of the second range
  if (first.start > second.end) {
    return false;
  }

  // Otherwise, the ranges must overlap
  return true;
}

int main() {
  // Open the input file
  std::ifstream file("example_input.txt");
  if (!file.is_open()) {
    std::cout << "Error: unable to open file" << std::endl;
    return 1;
  }

  // Define an array to store the range pairs
  RangePair pairs[100]; // Assume no more than 100 pairs

  // Read the range pairs from the file
  int numPairs = 0;
  std::string line;
  while (std::getline(file, line)) {
    // Parse the range values from the line
    std::sscanf(line.c_str(), "%d-%d,%d-%d", &pairs[numPairs].first.start, &pairs[numPairs].first.end, &pairs[numPairs].second.start, &pairs[numPairs].second.end);
    numPairs++;
  }

  // Close the input file
  file.close();

  // Keep track of the total number of overlapping range pairs
  int totalOverlap = 0;

  // Iterate over the range pairs
  for (int i = 0; i < numPairs; i++) {
    // Check if the current range pair overlaps
    if (rangesOverlap(pairs[i].first, pairs[i].second)) {
      totalOverlap++;
    }
  }

  // Print the total number of overlapping range pairs
  std::cout << "Total overlapping pairs: " << totalOverlap << std::endl;

  return 0;
}