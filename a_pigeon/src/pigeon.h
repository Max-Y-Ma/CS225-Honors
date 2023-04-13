/**
 * @file pigeon.h
 * Approximate Pattern Matching using pigeonhole
 */

#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <set>

// Type definitions used in this assignment
typedef std::unordered_map<std::string, std::vector<int> > kmerMap;
typedef std::pair<std::string, int> Seed;

/**
 * Takes a filename and reads in all the text from the file
 * Newline characters are also just characters in ASCII
 * 
 * @param filename The name of the file that will fill the string
 */
std::string file_to_string(const std::string& filename);

/**
 * Takes an input text and transforms it to a vector of all the kmers in that text.
 * A kmer is a fixed length substring (watch your edge cases!)
 * @param T A reference variable storing the input text
 * @param k The size of the kmer
 */
kmerMap text_to_kmer_map(std::string& T, int k);

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
std::vector<Seed> partitionPattern(std::string P, int numPart);

/**
 * Performs inexact pattern matching between input text and pattern
 * Returns a vector<int> of match index positions and offsets
 * You can implement this using any method you want.
 * You are strongly encouraged t use the Seed values and kmerMap
 * @param fname The input text file being indexed and then searched over
 * @param P The input pattern being searched for
 * @param mm The number of mismatches (defaults to one but others will be tested)
 */
std::vector<int> approximate_search(const std::string & fname, std::string P, int mm = 1);

// Helper Functions
int validAlignment(std::string T, std::string P, int Tindex, Seed parition);