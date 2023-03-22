/**
 * @file sarray.h
 * Declarations of suffix arrays for exact pattern matching.
 */

#pragma once

#include <string>
#include <vector>
#include <map>

// Your assignment is to build these two functions
std::vector<int> build_sarray(std::string T);
std::vector<int> sarray_search(std::string P, std::string T, std::vector<int> sarray);

// If you want to implement the two binary search method, these may be helpful!
// THESE ARE OPTIONAL FUNCTIONS THAT WONT BE TESTED DIRECTLY
int getSmallest(std::string P, std::string T, std::vector<int> sarray);
int getLargest(std::string P, std::string T, std::vector<int> sarray);