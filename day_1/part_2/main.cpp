#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

int main() {
  auto file_stream = std::ifstream{"input.txt"};

  if (!file_stream.is_open()) {
    std::cout << "Could not open file: 'input.txt'\n";
    return EXIT_FAILURE;
  }

  auto count = 0;
  auto measurement = 0;
  auto measurements = std::vector<int>{};

  while (file_stream >> measurement) {
    measurements.push_back(measurement);
  }

  file_stream.close();

  const auto size = measurements.size() - 3;

  for (auto i = std::size_t{0u}; i < size; ++i) {
    const auto first_window = measurements[i] + measurements[i + 1] + measurements[i + 2];
    const auto second_window = measurements[i + 1] + measurements[i + 2] + measurements[i + 3];

    if (second_window > first_window) {
      ++count;
    }
  }

  std::cout << "Result: " << count << '\n';

  return EXIT_SUCCESS; 
}