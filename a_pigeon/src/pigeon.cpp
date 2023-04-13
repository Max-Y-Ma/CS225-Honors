/**
 * @file pigeon.cpp
 * Approximate Pattern Matching using pigeonhole
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <algorithm>

#include "pigeon.h"

/**
 * Takes a filename and reads in all the text from the file
 * Newline characters are also just characters in ASCII
 * 
 * @param filename The name of the file that will fill the string
 */
std::string file_to_string(const std::string& filename){
  std::ifstream text(filename);

  std::stringstream strStream;
  if (text.is_open()) {
    strStream << text.rdbuf();
  }
  return strStream.str();
}

/**
 * Takes an input text and transforms it to a vector of all the kmers in that text.
 * A kmer is a fixed length substring (watch your edge cases!)
 * @param T A reference variable storing the input text
 * @param k The size of the kmer
 */
kmerMap text_to_kmer_map(std::string & T, int k) {
  // Add Substring to Hash Map
  kmerMap outMap;
  for (int i{0}; i <= static_cast<int>(T.length() - k); ++i)
  {
    // Add Index
    auto it = outMap.find(T.substr(i, k));
    if (it != outMap.end())
    {
      (it->second).push_back(i);
      continue;
    }
    // Add Substring
    outMap.insert({T.substr(i, k), {i}});
  }
  return outMap;
}

/**
 * Takes an input pattern and number of partitions and returns a vector of type Seed
 * 
 * Seed is a pair<string, int> containing the string partition and its starting index in P
 * The partitions are non-overlapping strings
 *
 * If there are excess characters (division is not a whole number)
 * distribute the characters round-robin starting with the first partition.
 * Ex: ABCD partitioned into three partitions is AB, C, D (The extra char goes to first partition)
 *
 * @param P The input pattern
 * @param numPart The number of partitions
 */
std::vector<Seed> partitionPattern(std::string P, int numPart) {
  std::cout << P << " " << numPart << std::endl;

  // Partition Length
  bool firstPartitionLengthDifferent = false;
  double d_partitionLength = ((double)P.length() / (double)numPart);
  
  if ((P.length() % numPart != 0) && d_partitionLength < ((P.length() / numPart) + 0.5))
  {
    firstPartitionLengthDifferent = true;
    d_partitionLength++;
  } 

  bool doneFirstPartition = false;
  int partitionLength = static_cast<int>(d_partitionLength + 0.5);
  // Create Partitions
  std::vector<Seed> outVec;
  for (int i{0}; i < numPart; ++i) 
  {
    if (firstPartitionLengthDifferent)
    {
      outVec.push_back({P.substr(i * partitionLength, partitionLength), i * partitionLength});
      partitionLength--;
      firstPartitionLengthDifferent = false;
      doneFirstPartition = true;
      continue;
    }

    outVec.push_back({P.substr(i * partitionLength + doneFirstPartition, partitionLength), i * partitionLength  + doneFirstPartition});
  }
  return outVec;
}

/**
 * Performs inexact pattern matching between input text and pattern
 * Returns a vector<int> of match index positions and offsets
 * You can implement this using any method you want.
 * You are strongly encouraged to use the Seed values and kmerMap
 * @param fname The input text file being indexed and then searched over
 * @param P The input pattern being searched for
 * @param mm The number of mismatches (defaults to one but others will be tested)
 */
std::vector<int> approximate_search(const std::string & fname, std::string P, int mm) {
  // Supporting Data Structures
  std::string T = file_to_string(fname);
  std::vector<Seed> partitions = partitionPattern(P, mm + 1);
  kmerMap kmap = text_to_kmer_map(T, (P.length() / (mm + 1)));

  // Check Alignments
  std::vector<int> outList;
  for (auto partition: partitions)
  {
    // Grab Partition Locations in KmerMap
    auto it = kmap.find(partition.first);
    if (it == kmap.end())
      continue;
    std::vector<int> locations = it->second;

    // For Each Location, Check Hamming Distance
    for (auto location: locations)
    {
      if (validAlignment(T, P, location, partition) <= mm) {
        outList.push_back(location - partition.second);
      }
    }
  }

  // No Valid Solutions
  if (outList.empty())
    return {-1};

  // Remove Duplicates
  sort(outList.begin(), outList.end());
  outList.erase(std::unique(outList.begin(), outList.end()), outList.end());

  return outList;
}

int validAlignment(std::string T, std::string P, int Tindex, Seed parition) {
  // Set Alignment
  int startIndex = Tindex - parition.second;
  if (startIndex < 0)
    startIndex = 0;

  // Out of Bounds
  if (startIndex + (int)P.length() > (int)T.length())
    return (int)T.length();

  // Check Alignment
  int mismatchCount = 0;
  for (int i{startIndex}; i < startIndex + (int)P.length(); ++i)
  {
    if (T.at(i) != P.at(i - startIndex))
      mismatchCount++;
  }

  return mismatchCount;
}