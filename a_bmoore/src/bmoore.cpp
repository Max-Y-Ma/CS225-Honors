/**
 * @file bmoore.cpp
 * Code to Boyer-Moore solution for exact pattern matching.
 * Uses strong bad character rule only
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <vector>

#include "bmoore.h"

/**
 * Takes in two strings (P and the alphabet) 
 * Returns a 2D array containing the skip values for bad character rule
 *
 * @param P A std::string object which holds the pattern being pre-processed.
 * @param alpha An std::string object which holds all characters in the alphabet of P and T.
 *
 * @return An std::vector<std::vector<int>> (a 2D array of integers) storing the bad character array
 * BC_array rows correspond to the alphabet and the columns correspond to positions along the pattern.
 */
std::vector<std::vector<int>> prep_bc_array(std::string P, std::string alpha) {
  // Bad Character Preprocessing
  std::vector<std::vector<int>> bc_array;

  // Iterate for Each Character in Alpha
  // Calculate Value for Each Character in Pattern Start at End
  int alpha_length = alpha.length();
  int p_length = P.length();
  int skips = 0;
  for (int i{0}; i < alpha_length; i++) {
    // Vector for Row in Alphabet
    std::vector<int> row;
    for (int j{0}; j < p_length; j++) {
      // Calculate Number Skips;
      skips = 0;
      while ((j - 1 - skips >= 0) && P.at(j - 1 - skips) != alpha.at(i)) {
        skips++;
      }
      row.push_back(skips);
    }
    // Expand Skip Table
    bc_array.push_back(row);
  }

  return bc_array;

}

/**
 * Returns the index positions of first instance of c in alpha.
 * If no match is found, returns the value '-1'
 *
 * A potentually useful helper function for relating characters to integers
 * As a fun fact, this was a valid solution to naive_search (Week 1)
 *
 * NOTE: This is not actually an efficient solution but we are handwaving it here.
 *
 * @param alpha A std::string object which holds the alphabet string.
 * @param c A char object which holds the character being searched for
 *
 * @return An integer containing the index position of c in alpha
 */
int findChar(std::string alpha, char c){
  return alpha.find(c);
}

/**
 * Returns the number of alignments skipped by Boyer-Moore
 * In this instance, Boyer-Moore is *only* the strong bad character rule [and right-to-left scanning]
 *
 * Also modifies the outlist vector to contain the index positions of all exact matches of P in T.
 * If no match is found, modifies the vector to contain one value '[-1]'
 *
 * @param P A std::string object which holds the Pattern string.
 * @param T A std::string object which holds the Text string.
 * @param alpha A std::string object which holds the Alphabet string.
 * @param outList An std::vector<int> array (by reference) that can be modified to contain all matches
 *
 * @return An int counting the number of skipped alignments using bad character.
 */
int bmoore_search(std::string P, std::string T, std::string alpha, std::vector<int> & outList) {
  // Preprocessing
  std::vector<std::vector<int>> bc_array = prep_bc_array(P, alpha);

  // Find Pattern
  // 1.) Keep track of current position (alighnment)
  // 2.) Use findChar to help find skip vector
  int skip = 0;
  outList.push_back(-1);

  // Iterate through whole string
  int T_length = T.length();
  int P_length = P.length();
  int i, j, num_skips;

  for (int index{0}; index < T_length; index++) {
    // Out of Bounds
    if (index > T_length - P_length) {
      break;
    }

    // Compare Alignment
    num_skips = 0;
    for (int pos{P_length - 1 + index}; pos >= index; pos--) {
      // Move to Next Alignment
      if (P.at(pos - index) == T.at(pos)) {
        // Found Matching Pattern
        if (pos == index) {
          // Remove -1 if empty
          if (outList.front() == -1) {
            outList.pop_back();
          }
          outList.push_back(pos);
        }
        continue;
      }
      // Bad Character: Determine Skips
      else {
        // pos and find in alphabet
        i = findChar(alpha, T.at(pos));
        j = pos - index;
        num_skips = (bc_array.at(i)).at(j);

        // Adjust Skips
        while ((P_length - 1 + index) + num_skips > T_length - 1) {
          num_skips--;
        }

        break;
      }
    }

    // Set Skips
    skip += num_skips;
    index += num_skips;
  }

  return skip;
}