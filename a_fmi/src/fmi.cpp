/**
 * @file fmi.cpp
 * Code to constructiong and searching a FM Index
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <algorithm>

#include "fmi.h"

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
* FM Index constructor; Given T, creates:
* a Burrows Wheeler Transform (BWT)
* a suffix array (SA)
* an occurence table (OT)
* @param T The string being preprocessed into an FM Index
* @param alpha The alphabet we are building our index around
* @param sr The sample rate for the SA and OT (Optional)
*/
FMI::FMI(std::string T, std::string a, int sr){
  sampleRate = sr; //A purely optional protected variable
  alpha = a;

  // Alphabet is sorted to minimize debug difficulties
  // Also makes code easier
  std::sort(alpha.begin(), alpha.end()); 

  // Your code must implement all three of these
  // Autograder will check each individually
  BWT = buildBWT(T);
  SA = buildSA(T);
  OT = buildOT(BWT);
}


/*
* Destructor for FM Index
*/
FMI::~FMI()
{
    /* nothing unless you added more variables */
}

/**
 * Returns the SA of T as a vector of ints
 *
 * @param T A std::string object which holds the text being pre-processed.
 *
 * @return An std::vector<int> storing the suffix array
 */
std::vector<int> FMI::buildSA(std::string T){
  std::vector<int> sarray;

  std::vector<std::pair<std::string, int>> sufList;
  
  T = T + "$";
  size_t tlen = T.size();

  for (size_t i = 0; i < tlen; ++i){
    std::string t_suf = T.substr(i);
    sufList.push_back(make_pair(t_suf, i));
  }

  std::sort(sufList.begin(),sufList.end()); 

  for (size_t i = 0; i < tlen; ++i){
      sarray.push_back(sufList[i].second);
  }

  return sarray;
}


/**
 * Returns the BWT of T as a string
 *
 * @param T A std::string object which holds the text being pre-processed.
 *
 * @return An std::string storing the BWT
 */
std::string FMI::buildBWT(std::string T){
  // Create All Rotations
  std::vector<std::string> BWT_matrix = rotate(T + '$');

  // Sort the Rotations
  std::sort(BWT_matrix.begin(), BWT_matrix.end());

  // Return the Last Column of BWT Matrix
  std::string BWT;
  for (auto e: BWT_matrix)
    BWT += e.back();

  // Store F
  for (auto e: BWT_matrix)
    F += e.front();

  return BWT;
}


/**
 * Returns the Occurrence Table of a BWT (A 2D table of tsize x alphabet)
 *
 * @param T A std::string object which holds the text being pre-processed.
 *        T in this instance is *usually* the BWT. 
 *        Other strings may be tested by the autograder
 *
 * @return An std::vector<std::vector<int>> storing the cumulative count
 *         of each character 
 *
 *         rows are alphabet in length (one row per individual index positions)
 */
std::vector<std::vector<int>> FMI::buildOT(std::string T){
  std::vector<std::vector<int>> OT;

  // Initialize Previous Row
  std::vector<int> previousRow;
  for (unsigned long i{0}; i < alpha.length(); ++i) 
    previousRow.push_back(0);

  // Create Occurrence Table
  for (unsigned long i{0}; i < T.length(); ++i) 
  {
    // Update Previous Row to Become Current Row
    for (unsigned long j{0}; j < alpha.length(); ++j) 
    {
      if (T.at(i) == alpha.at(j))
      {
        previousRow.at(j)++;
        break;
      }
    }
    // Add Current Row to Occurrence Table
    OT.push_back(previousRow);
  }

  return OT;
}

/**
* FM Index First Range Search
* Gives the index start and end position for the character 
* (and rank range) being searched
* 
* @param c The character being looked up
* @param s_rank The starting rank being searched 
* @param e_rank The ending rank being searched 
*
* HINT: You will have to reconstruct F from the BWT or the OT
*/
std::pair<int, int> FMI::get_frange(std::string c, int s_rank, int e_rank){
  std::pair<int, int> out;

  // Find Indexes
  bool firstMatch = false;
  int rank = 0;
  for (unsigned long i{0}; i < F.length(); ++i) 
  {
    if (F.at(i) == c.at(0) && !firstMatch) 
    {
      if (rank >= s_rank)
      {
        out.first = i;
        firstMatch = true;
      }
      rank++;
    }

    else if (F.at(i) == c.at(0) && rank <= e_rank && firstMatch)
    {
      out.second = i;
      rank++;
    }
  }

  if (s_rank == e_rank) {
    out.second = out.first;
  }

  return out;
}

/**
* FM Index Last Range Search
* Gives the number of occurrences of character *before* s_index (s_rank)
* and the number of occurrences of character at the e_index 
* 
* @param c The character being looked up
* @param s_index The starting index being searched 
* @param e_index The ending index being searched 
*
* HINT: L is the BWT, s_index *cannot* be 0. Why?
*/
std::pair<int, int> FMI::get_lrange(std::string c, int s_index, int e_index){
  std::pair<int, int> out;

  // Find Indexes
  int s = false;
  int start = -1;
  int end = -1;
  for (unsigned long i{static_cast<unsigned long>(s_index)}; i <= static_cast<unsigned long>(e_index); ++i) 
  {
    if (BWT.at(i) == c.at(0) && !s) 
    {
      start = i;
      end = i;
      s = true;
    }
    else if (BWT.at(i) == c.at(0) && s)
    {
      end = i;
    }
  }

  // Grab Indexes from OT
  int column = 0;
  for (unsigned long i{0}; i < alpha.length(); ++i)
  {
    if (alpha.at(i) == c.at(0))
      column = i;
  }

  if (start == -1 && end == -1)
  {
    return std::make_pair(0, 0);
  }

  out.first = (OT.at(start - 1)).at(column);
  out.second = (OT.at(end)).at(column);

  return out;
}


/**
 * Performs exact pattern matching on the FM Index for input P
 *
 * @param P A std::string object which holds the pattern being searched.
 *
 * @return An std::vector<int> storing the index positions of matches
 *         or returns {-1} if there is no match
 */
std::vector<int> FMI::search(std::string P){
  std::vector<int> outList;

  std::string c = P.substr(P.size()-1,1);

  int letter = alpha.find(c);
  
  // If letter not in alphabet, stop searching
  if (letter == -1){
    outList.push_back(-1);
    return outList;
  }
  
  // F column can be represented by the occurrence # of each character
  std::vector<int> F = OT.back();

  // Our first occurrence of char c has rank 0
  // Our last occurrence of char c has rank # occurrences - 1
  // @TODO: REPLACE THESE VALUES WITH THE APPROPRIATE STARTING VALUES
  int s_rank = -1;
  int e_rank = -1; //HINT: How do I know the # occurrences?

  // If my last occurrence has rank -1, it means I never saw the character at all.
  if (e_rank == -1){
    outList.push_back(-1);
    return outList;
  }

  // Get the initial F range to search (Index start - Index end)
  // You will have to code get_frange to match this code
  std::pair<int,int> frange = get_frange(c, s_rank, e_rank);

  // FMI logic finds range of occurrences (using L), then finds FM index range to search (in F)
  // In other words:
  // lrange outputs # of occurrences before start index and at end index
  // These occurrence numbers determine the range start and end values, used by frange.
  //
  // frange outputs index start and end
  // These index positions are used by lrange directly
  // 
  // The final frange (index start and end) tells us which suffix array values to look up
  for(int i = P.size()-2; i >= 0; i--){
    c = P.substr(i,1);

    letter = alpha.find(c);

    //Gets the start and end rank values for c_{i-1} based on index start and end for c_{i}
    // (Recall that we are starting from i = size()-1)
    // You will have to code get_lrange to match this code
    std::pair<int,int> lrange = get_lrange(c, frange.first, frange.second);

    // @TODO: REPLACE THIS VALUE WITH THE APPROPRIATE VALUES
    int numMatches = -1;

    // If lrange returns the same value start to end, we have no characters in range.
    if(numMatches <= 0){
      outList.push_back(-1);
      return outList;
    }

    // Given our range values we want the index values
    // Recall that lrange outputs occurrences not ranges
    // The occurrence # before our first index is our first rank -- why?
    // The occurrence # at our last position MINUS 1 is our last rank -- why?
    frange = get_frange(c, lrange.first, lrange.second - 1);

    if( frange.first == -1 || frange.second == -1){
      outList.push_back(-1);
      return outList;
    }
  }

  // @TODO: WRITE CODE TO ADD ALL MATCHES TO outList 
  

  return outList;
}