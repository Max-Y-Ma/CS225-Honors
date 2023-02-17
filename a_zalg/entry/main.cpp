/**
 * @file main.cpp
 * A simple C++ program for running the Z-algorithm.
 */

#include <string>
#include <iostream>
#include <vector>

#include "zalg.h"

int main() {
  std::cout << "example 1" << std::endl;

  std::string P = "aaaaa";
  std::string T = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

  std::string S = P + "$" + T;

  int *zarr = new int[S.length()];

  int charComps = create_zarray(S,zarr);

  std::cout << charComps << std::endl;
  
  
  // Code to print a Z-array to terminal
  std::cout << "{";
  for (unsigned i = 0; i < S.length()-1; ++i){
    std::cout << zarr[i] << ", ";
  }
  std::cout << zarr[S.length()-1] << "}" << std::endl;

/*
  IF YOU WANT TO TEST ZALG SEARCH UNCOMMENT THIS (AFTER IMPLEMENTING)

  std::vector<int> outList = zalg_search(P, T);

  // Code to loop through all values in std::vector<int> outList
  // Note if no match is found, vector still not empty
  std::cout << "{";
  for (int val : outList){
    std::cout << val << ", ";
  }
  std::cout << "}" << std::endl;
  */

  delete[] zarr;


  return 0;
}
