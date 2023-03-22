/**
 * @file sarray.cpp
 * Code to using suffix arrays for exact pattern matching.
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <algorithm>

#include "sarray.h"


/**
 * Returns the suffix array of T as an int vector.
 *
 * @param T A std::string object which holds the text being pre-processed.
 *
 * @return An std::vector<int> storing the suffix array
 */
std::vector<int> build_sarray(std::string T) {
  // Create Unsorted Suffix Array Containing Strings
  std::vector<std::string> sarray_string;
  int pos = T.length();
  for (unsigned long i{0}; i < T.length() + 1; i++) {
    sarray_string.push_back(T.substr(pos, i) + '$');
    pos--;
  }

  // Sort Suffix Array Containing Strings
  std::sort(sarray_string.begin(), sarray_string.end());
  
  // Convert to Integer
  std::vector<int> sarray;
  for (auto element: sarray_string)
    sarray.push_back(T.length() + 1 - element.size());

  return sarray;
}


/**
 * Returns a vector of indices containing all exact pattern match locations
 *
 * @param P A std::string object which holds the pattern being searched
 * @param T A std::string object which holds the text the SA is built on [excluding '$']
 * @param sarray A std::vector<int> which holds the suffix array
 *
 * @return An std::vector<int> storing all matching index positions
 * NOTE: For full credit, you must use the suffix array
 */
std::vector<int> sarray_search(std::string P, std::string T, std::vector<int> sarray) {
  T = T+"$"; 

  std:: cout << T << std::endl;
  std:: cout << P << std::endl;

  // Find the Smallest Index
  int start_index = getSmallest(P, T, sarray);

  // Find the Largest Index
  int end_index = getLargest(P, T, sarray);

  // If Index are both -1 Return {-1}
  if (start_index == -1 && end_index == -1)
    return {-1};
  
  // Return Values in that Range
  std::vector<int> outList;
  
  outList.assign(sarray.begin() + start_index, sarray.begin() + end_index + 1);
  return outList; 
}

int _getSmallest(std::string P, std::vector<std::string> s, std::string T, int low, int high) {
  // Remember Last Match Index
  static int index = -1;

  // Base Case: Low > High
  if (low > high || low == static_cast<int>(T.length()))
    return index;

  // Recursive Checks
  int midpoint = (low + high) / 2;
  int compare_value = (s.at(midpoint)).compare(0, P.size(), P);
  if (compare_value == 0) {
    index = midpoint;

    // Assume there is a smaller index
    _getSmallest(P, s, T, low, midpoint - 1);
  }
  // P is Right Side
  else if (compare_value < 0) {
    _getSmallest(P, s, T, midpoint + 1, high);
  }
  // P is Left Side
  else {
    _getSmallest(P, s, T, low, midpoint - 1);
  }

  return index; 
}

// Binary Search for P in T, Assuming Query is Smaller on Match
int getSmallest(std::string P, std::string T, std::vector<int> sarray) {
  // Reconstruct String Suffix Array
  std::vector<std::string> sarray_string;
  for (unsigned long i{0}; i < T.length(); i++) {
    sarray_string.push_back(T.substr(sarray.at(i)));
  }

  // Use Smallest Binary Search Helper
  return _getSmallest(P, sarray_string, T, 0, sarray_string.size());
}

int _getLargest(std::string P, std::vector<std::string> s, std::string T, int low, int high) {
  // Remember Last Match Index
  static int index = -1;

  // Base Case: Low > High
  if (low > high || low == static_cast<int>(T.length()))
    return index;

  // Recursive Checks
  int midpoint = (low + high) / 2;
  int compare_value = (s.at(midpoint)).compare(0, P.size(), P);
  if (compare_value == 0) {
    index = midpoint;

    // Assume there is a smaller index
    _getLargest(P, s, T, midpoint + 1, high);
  }
  // P is Right Side
  else if (compare_value < 0) {
    _getLargest(P, s, T, midpoint + 1, high);
  }
  // P is Left Side
  else {
    _getLargest(P, s, T, low, midpoint - 1);
  }

  return index; 
}

// Binary Search for P in T, Assuming Query is Larger on Match
int getLargest(std::string P, std::string T, std::vector<int> sarray) {
  // Reconstruct String Suffix Array
  std::vector<std::string> sarray_string;
  for (unsigned long i{0}; i < T.length(); i++) {
    sarray_string.push_back(T.substr(sarray.at(i)));
  }

  // Use Largest Binary Search Helper
  return _getLargest(P, sarray_string, T, 0, sarray_string.size());
}