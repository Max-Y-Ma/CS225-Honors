/**
 * @file main.cpp
 * A simple C++ program for building a suffix array and searching it.
 */

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "sarray.h"

int main() {


  std::cout << "example 1" << std::endl;

  std::string P = "C";
  std::string T = "AAAABBBB";

  std::vector<int> sa = build_sarray(T);

  std::cout << "Sarray values:" << std::endl;
  std::cout << "{ ";
  for (int i = 0; i < (int) sa.size(); ++i){
      std::cout << sa[i] << ", ";
  }
  std::cout << "}" << std::endl;

  std::vector<int> lV = sarray_search(P,T,sa);

  std::cout << "Sarray search output:" << std::endl;
  std::cout << "{ ";
  for (int i = 0; i < (int) lV.size(); ++i){
      std::cout << lV[i] << ", ";
  }
  std::cout << "}" << std::endl;


  // If you choose to implement these optional functions, can test by uncommenting.
  // std::cout << "Smallest: " << getSmallest(P,T,sa) << std::endl;
  // std::cout << "Largest: " << getLargest(P,T,sa) << std::endl;

  return 0;
}
