#include <iostream>
#include "dynamic_array.hpp"

int main() {
  dynamic_array array = dynamic_array<int, 3>();
  array.push_back(2);
  array.push_back(3);
  array.push_back(4);

  std::cout << array.size() << std::endl;
  array.push_back(5);
  std::cout << array.size() << std::endl;



  dynamic_array array2 = dynamic_array<int, 3>{2,3,4};

  bool check = array==array2;
  std::cout << "check if arrays are equal " << check << std::endl;

  std::cout << "itterate over array" << std::endl;

  auto f = std::find(array.begin(), array.end(), 2);
  if (f != array.end())
    std::cout << "Element found in array: " << *f << '\n';
  else
    std::cout << "Element not found in array\n";

  array[0] = 1;

  auto j = std::find(array.begin(), array.end(), 2);
  if (j != array.end())
    std::cout << "Element found in array: " << *j << '\n';
  else
    std::cout << "Element not found in array\n";


  return 0;
}