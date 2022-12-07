#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

// it doesnt work... but that doesnt seem to be GPT fault.. just copying and pasting adds spaces where newlines exist

int main() {
  // Open the file for reading
  std::ifstream input_file("example_input.txt");

  // Check if the file was opened successfully
  if (!input_file.is_open()) {
    std::cerr << "Failed to open file.txt" << std::endl;
    return 1;
  }

  // Read the file into a string
  std::string file_contents((std::istreambuf_iterator<char>(input_file)),
                            std::istreambuf_iterator<char>());

  // Split the string into lines
  std::vector<std::string> lines;
  size_t start = 0;
  size_t end = file_contents.find('\n', start);
  while (end != std::string::npos) {
    lines.push_back(file_contents.substr(start, end - start));
    start = end + 1;
    end = file_contents.find('\n', start);
  }
  lines.push_back(file_contents.substr(start));

  // Convert each line to a vector of integers
  std::vector<std::vector<int>> numbers;
  for (const auto& line : lines) {
    std::vector<int> row;
    size_t pos = 0;
    while (pos != line.size()) {
      // Find the next number in the line
      int number;
      size_t next = line.find(' ', pos);
      if (next == std::string::npos) {
        next = line.size();
      }
      number = stoi(line.substr(pos, next - pos));
      row.push_back(number);
      pos = next + 1;
    }

    // Add the row to the numbers vector
    numbers.push_back(row);
  }

  // Find the row with the maximum sum
  size_t max_row = 0;
  int max_sum = std::accumulate(numbers[0].begin(), numbers[0].end(), 0);
  for (size_t i = 1; i < numbers.size(); i++) {
    int sum = std::accumulate(numbers[i].begin(), numbers[i].end(), 0);
    if (sum > max_sum) {
      max_row = i;
      max_sum = sum;
    }
  }

  // Print the result
  std::cout << "The elf carrying the most calories is Elf #" << max_row + 1
            << " with a total of " << max_sum << " calories." << std::endl;

  // Close the file
  input_file.close();

  return 0;
}