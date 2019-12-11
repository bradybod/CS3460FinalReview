#include <iostream>
#include "dynamic_array.hpp"

int main() {
  dynamic_array array = dynamic_array<int, 6>();
  array.push_back(2);
  array.push_back(3);
  array.push_back(4);
  std::cout << array[2] << std::endl;
  return 0;
}