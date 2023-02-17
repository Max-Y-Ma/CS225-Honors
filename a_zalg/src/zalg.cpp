/**
 * @file zalg.cpp
 * Code to create Z-array and use Z-algorithm for exact pattern matching.
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "zalg.h"

// Returns the Z value for given string, S, and position
int compute_Z(std::string S, cs225::zstring& inS, int position, int offset) {
  /* Pseudocode:
    * 1.) Compare character at position to first character in S 
      * a.) Continue until no match, tracking the number of comparisons
      * b.) Z-value is the number of matching comparisons
  */
  int Z_value = 0;
  for (unsigned long i{0}; i < S.length() - position; i++) {
    // If Equal Comparison, increment Z-value
    if (inS.charMatch(i + offset, i + position)) {
      Z_value++;
    }
    // Otherwise, break
    else {
      return Z_value;
    }
  }

  return Z_value;
}

/**
 * Returns the number of individual character comparisons used by the Z-algorithm
 * Also modifies the input (empty) zArray to store the Z-value at each position i>0
 *
 * @param S A std::string object which holds the String being analyzed.
 * @param Z An int* that points to a length |S| int[] which holds the zArray.
 *
 * @return An integer counting the number of character comparisons needed to make the Z-array.
 */
int create_zarray(std::string S, int* Z) {
  // You need to track character comparisons. Here are two suggested ways: 
  cs225::zstring inS(S); //Use 'cs225::zstring' to automatically track comparisons

  // Skip First Position in Z
  *Z = 0;

  // Iterate for all positions in string
  int B, k;
  for (unsigned long j{1}; j < S.length(); j++) {
    // Case #1: i > r -> Compute Zi
    if (inS.i > inS.r) {
      *(Z + inS.i) = compute_Z(S, inS, inS.i, 0);
      // Double Check This
      inS.r = inS.i + (*(Z + inS.i) - 1);
      inS.l = inS.i;
    }
    // Case #2: i <= r
    else if (inS.i <= inS.r) {
      // Compute |B| and k
      B = inS.r - inS.i + 1;
      k = inS.i - inS.l;

      // Case #2a: Zk < |B| -> Zi = Zk
      if (*(Z + k) < B) {
        *(Z + inS.i) = *(Z + k);
      }
      // Case #2b: Zk = |B| -> Zi = Zk + Comparison start @ r + 1
      else if (*(Z + k) == B) {
        *(Z + inS.i) = *(Z + k) + compute_Z(S, inS, inS.r + 1, inS.r - inS.i + 1);
        // Double Check This
        inS.r = inS.r + (*(Z + inS.i) - *(Z + k));
        inS.l = inS.i;
      }
      // Case #2c: Zk > |B| -> Zi = |B|
      else if (*(Z + k) > B) {
        *(Z + inS.i) = B;
      }
    }

    // Move indexes
    if (inS.i > inS.r) {
      inS.r = inS.i;
      inS.l = inS.i;
    }
    
    inS.i++;

  }
  
  return inS.getCharComps();
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
std::vector<int> zalg_search(std::string P, std::string T) {
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