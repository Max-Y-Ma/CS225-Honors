/**
 * @file zval.cpp
 * Code to create Z-array and use Z-values for exact pattern matching.
 */

#include <iostream>
#include <cmath>
#include <cstdlib>

#include "zval.h"

/**
 * Returns the number of character comparisons required to find the first mismatch
 * or to completely match strings X and Y.
 *
 * @param X A std::string object which holds the first string being matched
 * @param Y An std::string object which holds the second string being matched
 *
 * @return An std::pair<int, int>. 
 *         The first value is the number of individual character comparisons needed.
 *         The second value is the longest common prefix length (match length)
 */

 std::pair<int,int> lr_scan(std::string X, std::string Y){
  std::pair<int, int> out = std::make_pair(0,0);

  // Compare each string position by position only iterating for shortest length
  int length = 0;
  if (X.length() < Y.length()) {
    length = X.length();
  } else {
    length = Y.length();
  }

  for (int i{0}; i < length; i++) {
    if (X.at(i) != Y.at(i)) {
      out.first++;
      break;
    }
    out.second++;
    out.first++;
  }

  return out;
 }


/**
 * Returns an array which stores the Z-value at each position i<0
 * The 0th position (i=0) should store the total number of 
 * Also modifies the input (empty) zArray to store the Z-value at each position i<0
 *
 * @param S A std::string object which holds the String being analyzed.
 * @param Z An int* that points to a length |S| int[] which holds the zArray.
 *
 * @return An integer counting the number of character comparisons needed to make the Z-array.
 */
int create_zarray(std::string S, int* Z) {
  int charComps = 0;

  // Iterate through all suffix position
  Z[0] = 0;
  for (unsigned int i{1}; i < S.length(); i++) {
    std::pair<int, int> result = lr_scan(S, S.substr(i, S.length() - i)); 
    charComps += result.first;
    Z[i] = result.second;
  }

  return charComps;
}


/**
 * Returns the index positions of all exact matches of P in T.
 * If no match is found, returns a vector with one value '[-1]'
 * NOTE: We want the exact matches *in T* not string S.
 *
 * Search the Text string (T) for the Pattern string (P)
 * For example, if P = 'AAA' and T = 'BAAAT', will return 1
 *
 * @param P A std::string object which holds the Pattern string.
 * @param T A std::string object which holds the Text string.
 *
 * @return An std::vector<int> array containing ALL index matches.
 */
std::vector<int> zval_search(std::string P, std::string T) {
  std::vector<int> outList;
  
  // NOTE: You should change this function as necessary to complete the assignment.
  std::string S = P + '$' + T;
  
  int *zarr = new int[S.length()];

  int charComps = create_zarray(S, zarr);

  for (unsigned int i{0}; i < S.length(); i++) {
    if (static_cast<unsigned int>(zarr[i]) == P.length()) {
      outList.push_back(i - P.length() - 1);
    }
  }

  // The vector can check if it is currently empty
  if (outList.empty()) {
    outList.push_back(-1);
    return outList;
  }

  delete[] zarr; // No memory leaks here!

  return outList;
}