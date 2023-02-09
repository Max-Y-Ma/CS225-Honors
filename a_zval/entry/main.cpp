/**
 * @file main.cpp
 * A simple C++ program for running the Z-algorithm.
 */

#include <string>
#include <iostream>
#include <vector>

#include "zval.h"

int main() {
  std::cout << "example 1" << std::endl;

  std::string P = "pattern";
  std::string T = "this is a pattern that has a repeat pattern";

  // Example run code for lr_scan
  std::pair<int, int> op = lr_scan(P,T);

  int charComps = op.first;
  int matchLength = op.second;

  std::cout << charComps << " " << matchLength << std::endl;

  // Example run code for create_zarray
  std::string S = "AAA$BAAAT";

  int *zarr = new int[S.length()];

  int cc = create_zarray(S,zarr);
  
  std::cout << cc << std::endl;
  
  // Code to print a Z-array to terminal
  std::cout << "{";
  for (unsigned i = 0; i < S.length()-1; ++i){
    std::cout << zarr[i] << ", ";
  }
  std::cout << zarr[S.length()-1] << "}" << std::endl;

  // Example run code for zval_search
  std::vector<int> outList = zval_search(P, T);


  // Code to loop through all values in std::vector<int> outList
  // Note if no match is found, vector still not empty
  std::cout << "{";
  for (int val : outList){
    std::cout << val << ", ";
  }
  std::cout << "}" << std::endl;

  delete[] zarr;


  return 0;
}
