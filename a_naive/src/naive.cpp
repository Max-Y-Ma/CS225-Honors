/**
 * @file naive.cpp
 * Intro to strings, pattern matching, and prefix/suffixes .
 */

#include <iostream>
#include <cmath>
#include <cstdlib>

#include "naive.h"

/**
 * Returns the index position of the first exact match of P in T.
 * If no match is found, returns the value '-1'
 *
 * Search the Text string (T) for the Pattern string (P)
 * For example, if P = 'AAA' and T = 'BAAAT', will return 1
 *
 * @param P A std::string object which holds the Pattern string.
 * @param T A std::string object which holds the Text string.
 *
 * @return An integer.
 */
int naive_search(std::string P, std::string T) {
  // Iterate through all substrings in T, the text string
  for (unsigned long i{0}; i < T.length(); i++) {
    std::string substring = T.substr(i, P.length());
    if (P == substring) {
      return i;
    }
  }

  // Return -1, no match found
  return -1;
}

/**
 * Returns the string corresponding to the longest common prefix between P and T
 * If there is no common prefix, returns an empty string.
 *
 * @param P A std::string object which holds the Pattern string.
 * @param T A std::string object which holds the Text string.
 *
 * @return An std::string.
 */
std::string longest_common_prefix(std::string P, std::string T) {
  // Loop through the text string front to back looking for prefix.
  // Then shorten the prefix by 1 character and search again.
  for (unsigned long i{0}; i < P.length(); i++) {
    std::string prefix = P.substr(0, P.length() - i);
    std::string substring = T.substr(0, prefix.length());
      if (prefix == substring) {
        return substring;
      }
  }
  // No string found, return empty string
  return "";
}

/**
 * Returns the string corresponding to the longest common suffix between P and T
 * If there is no common suffix, returns an empty string.
 *
 * @param P A std::string object which holds the Pattern string.
 * @param T A std::string object which holds the Text string.
 *
 * @return An std::string.
 */
std::string longest_common_suffix(std::string P, std::string T) {
  for (unsigned long i{0}; i < P.length(); i++) {
    std::string suffix = P.substr(i, P.length() - i);
    std::string substring = T.substr(T.length() - suffix.length(), suffix.length());
      if (suffix == substring) {
        return substring;
      }
  }

  return "";
}


