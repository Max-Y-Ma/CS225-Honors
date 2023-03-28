/**
 * @file bwt.cpp
 * Code to encoding and decoding a text using the BWT
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <algorithm>

#include "bwt.h"

/**
 * Returns a vector of strings containing all rotations of a text
 *
 * @param T A std::string object which holds the text being pre-processed.
 *
 * @return An std::vector<std::string> storing all rotations
 */
std::vector<std::string> rotate(std::string T){
  std::vector<std::string> out;
  for (unsigned long i{0}; i < T.length(); ++i) {
    // Add Current Rotation
    out.push_back(T); 

    // Apply Rotation
    char temp = T.back();
    T.replace(1, T.length(), T.substr(0, T.length() - 1));
    T.front() = temp;
  }

  return out;
}


/**
 * Returns the BWT of T as a string
 *
 * @param T A std::string object which holds the text being pre-processed.
 *
 * @return An std::string storing the BWT
 */
std::string encode_bwt(std::string T){
  // Create All Rotations
  std::vector<std::string> BWT_matrix = rotate(T + '$');

  // Sort the Rotations
  std::sort(BWT_matrix.begin(), BWT_matrix.end());

  // Return the Last Column of BWT Matrix
  std::string BWT;
  for (auto e: BWT_matrix)
    BWT += e.back();

  return BWT;
}

/**
 * Returns the BWT of T as a string
 *
 * @param T A std::string object which holds the text being pre-processed.
 *
 * @return An std::string storing the BWT
 */

std::string decode_bwt(std::string bwt){
  // Store BWT Matrix w/ Each String as a Row
  std::vector<std::string> BWT_matrix;

  // Initialize Matrix
  for (unsigned long i{0}; i < bwt.length(); ++i) {
    BWT_matrix.push_back("");
  }

  // Reconstruct BWT Matrix
  for (unsigned long i{0}; i < bwt.length(); ++i) {
    // Prepend Each Character of BWT to each Row
    for (unsigned long j{0}; j < bwt.length(); ++j) {
      BWT_matrix.at(j).insert(0, 1, bwt.at(j));
    }
    // Sort Each Row During Prepend
    sort(BWT_matrix.begin(), BWT_matrix.end());
  }

  // Return Row Ending with $
  for (auto e: BWT_matrix) {
    if (e.back() == '$')
      return e.substr(0, e.length() - 1);
  }

  return "";
}
