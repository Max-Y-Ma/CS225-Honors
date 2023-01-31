/**
 * @file main.cpp
 * A simple C++ program that tests your basic string functions
 */

#include <string>
#include <iostream>

#include "naive.h"

int main() {
  std::string P = "AAA";
  std::string T = "BAAAT";

  std::cout << "test 1" << std::endl;
  std::cout << naive_search(P, T) << std::endl;
  std::cout << longest_common_prefix(P, T) << std::endl;
  std::cout << longest_common_suffix(P, T) << std::endl;

  P = "AA";
  T = "AAAT";

  std::cout << "test 2" << std::endl;
  std::cout << naive_search(P, T) << std::endl;
  std::cout << longest_common_prefix(P, T) << std::endl;
  std::cout << longest_common_suffix(P, T) << std::endl;

  P = "ZZZ";
  T = "ZZZZ";

  std::cout << "test 3" << std::endl;
  std::cout << naive_search(P, T) << std::endl;
  std::cout << longest_common_prefix(P, T) << std::endl;
  std::cout << longest_common_suffix(P, T) << std::endl;

  P = "science";
  T = "Computer science is a lot of fun!";

  std::cout << "test 4" << std::endl;
  std::cout << naive_search(P, T) << std::endl;
  std::cout << longest_common_prefix(P, T) << std::endl;
  std::cout << longest_common_suffix(P, T) << std::endl;

  P = "pattern";
  T = "this is a pattern that has a repeat pattern";
  std::cout << "test 5" << std::endl;
  std::cout << naive_search(P, T) << std::endl;
  std::cout << longest_common_prefix(P, T) << std::endl;
  std::cout << longest_common_suffix(P, T) << std::endl;

  P = "Matters";
  T = "It matters that the third matters Matters. It also Matters that this sentence also matters";
  std::cout << "test 6" << std::endl;
  std::cout << naive_search(P, T) << std::endl;
  std::cout << longest_common_prefix(P, T) << std::endl;
  std::cout << longest_common_suffix(P, T) << std::endl;

 P = "an apple a day keeps the doctor away";
 T = "an apple a day beep boop gibberish hip hip hurray";

  std::cout << "test 7" << std::endl;

  std::cout << longest_common_prefix(P, T) << std::endl;
  std::cout << longest_common_suffix(P, T) << std::endl;

  return 0;
}
