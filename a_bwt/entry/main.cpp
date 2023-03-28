/**
 * @file main.cpp
 * A simple C++ program for encoding and decoding a text using the BWT.
 */

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "bwt.h"

int main() {


  std::cout << "example 1" << std::endl;

  std::string T = "This_is_a_simple_sample_text";

  // If you would like to test rotation function:
  /*
  std::vector<std::string> rot = rotate(T+"$");

  std::cout << "{ ";
  for (int i = 0; i < (int) rot.size(); ++i){
      std::cout << rot[i] << ", ";
  }
  std::cout << "}" << std::endl;
  */

  std::string bwt = encode_bwt(T);

  std::cout << "\"" << bwt << "\"" << std::endl;

  std::cout << "Original: " << decode_bwt(bwt) << std::endl;

  return 0;
}
