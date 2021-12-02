#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

struct position {
  int horizontal{};
  int depth{};
  int aim{};
};

int main() {
  auto file_stream = std::ifstream{"input.txt"};

  if (!file_stream.is_open()) {
    std::cout << "Could not open file: 'input.txt'\n";
    return EXIT_FAILURE;
  }

  auto current_position = position{0, 0, 0};
  auto command = std::string{};
  auto amount = 0;

  while (file_stream >> command >> amount) {
    if (command == "forward") {
      current_position.horizontal += amount;
      current_position.depth += current_position.aim * amount;
    } else if (command == "up") {
      current_position.aim -= amount;
    } else if (command == "down") {
      current_position.aim += amount;
    }
  }

  file_stream.close();

  const auto result = current_position.horizontal * current_position.depth;

  std::cout << "Result: " << result << '\n';

  return EXIT_SUCCESS; 
}