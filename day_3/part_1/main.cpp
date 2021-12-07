#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int convert_to_int(const std::vector<int>& binary) {
  auto result = 0;

  for (auto i = std::size_t{0u}; i < binary.size(); ++i) {
    result += binary[i] * static_cast<int>(std::pow(2, binary.size() - i - 1));
  }

  return result;
}

int main() {
  auto file_stream = std::ifstream{"input.txt"};

  if (!file_stream.is_open()) {
    std::cout << "Could not open file: 'input.txt'\n";
    return EXIT_FAILURE;
  }

  auto frequencies = std::vector<int>{};
  auto line = std::string{};
  auto entry_count = 0;

  while (file_stream >> line) {
    const auto size = line.size();

    if (frequencies.size() == 0) {
      frequencies.resize(size);
    }

    for (auto i = std::size_t{0}; i < size; ++i) {
      const auto value = line[i] - '0';
      
      if (value == 1) {
        frequencies[i] += 1;
      }
    }

    ++entry_count;
  }

  const auto frequency_count = frequencies.size();

  auto most_common = std::vector<int>{};
  most_common.reserve(frequency_count);


  auto least_common = std::vector<int>{};
  least_common.reserve(frequency_count);

  for (const auto frequency : frequencies) {
    if (frequency > entry_count / 2) {
      most_common.push_back(1);
      least_common.push_back(0);
    } else {
      most_common.push_back(0);
      least_common.push_back(1);
    }
  }

  const auto gamma_rate = convert_to_int(most_common);
  const auto epsilon_rate = convert_to_int(least_common);

  const auto result = gamma_rate * epsilon_rate;

  std::cout << "Result: " << result << "\n";

  return EXIT_SUCCESS; 
}