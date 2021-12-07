#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int convert_to_int(const std::string& binary) {
  auto result = 0;

  for (auto i = std::size_t{0u}; i < binary.size(); ++i) {
    result += (binary[i] - '0') * static_cast<int>(std::pow(2, binary.size() - i - 1));
  }

  return result;
}

template<typename Criteria>
std::vector<std::string> find(const std::vector<std::string>& entries, std::size_t index, Criteria&& criteria) {
  auto filtered = std::vector<std::string>{};
  
  if (entries.size() == 1) {
    return entries;
  }

  auto ones_count = 0u;

  for (const auto entry : entries) {
    const auto value = entry[index] - '0';
    if (value == 1) {
      ++ones_count;
    }
  }

  const auto searched_value = criteria(ones_count, entries.size());

  for (auto entry : entries) {
    if (entry[index] == searched_value) {
      filtered.push_back(entry);
    }
  }

  return find(filtered, index + 1, std::forward<Criteria>(criteria));
}

int main() {
  auto file_stream = std::ifstream{"input.txt"};

  if (!file_stream.is_open()) {
    std::cout << "Could not open file: 'input.txt'\n";
    return EXIT_FAILURE;
  }

  auto entries = std::vector<std::string>{};
  auto line = std::string{};

  while (file_stream >> line) {
    entries.push_back(line);
  }

  const auto oxygen_criteria = [](const auto ones_count, const auto total_count) {
    const auto zeros_count = total_count - ones_count;

    if (ones_count == zeros_count) {
      return '1';
    }

    return ones_count > zeros_count ? '1' : '0';
  };

  const auto co2_criteria = [](const auto ones_count, const auto total_count) {
    const auto zeros_count = total_count - ones_count;

    if (ones_count == zeros_count) {
      return '0';
    }

    return ones_count > zeros_count ? '0' : '1';
  };

  const auto oxygen_entries = find(entries, 0, oxygen_criteria);

  if (oxygen_entries.size() != 1) {
    std::cout << "Could not find the oxygen generator rating!\n";
    return EXIT_FAILURE;
  }

  const auto oxygen_rating = convert_to_int(oxygen_entries[0]);

  std::cout << "Oxygen generator rating: " << oxygen_rating << "\n";

  const auto co2_entries = find(entries, 0, co2_criteria);

  if (co2_entries.size() != 1) {
    std::cout << "Could not find the co2 scrubber rating!\n";
    return EXIT_FAILURE;
  }

  const auto co2_rating = convert_to_int(co2_entries[0]);

  std::cout << "Co2 scrubber rating: " << co2_rating << "\n";

  auto result = oxygen_rating * co2_rating;

  std::cout << "Result: " << result << "\n";

  return EXIT_SUCCESS; 
}