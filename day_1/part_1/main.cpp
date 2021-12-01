#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>

int main() {
  auto file_stream = std::ifstream{"input.txt"};

  if (!file_stream.is_open()) {
    std::cout << "Could not open file: 'input.txt'\n";
    return EXIT_FAILURE;
  }

  auto count = 0;
  auto current = 0;
  auto previous = std::numeric_limits<int>::max();

  while (file_stream >> current) {
    if (current > previous) {
      ++count;
    }
    previous = current;
  }

  file_stream.close();

  std::cout << "Result: " << count << '\n';

  return EXIT_SUCCESS; 
}