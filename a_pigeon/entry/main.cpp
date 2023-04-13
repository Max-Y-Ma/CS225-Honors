/**
 * @file main.cpp
 * A simple C++ program for exploring the pigeonhole principle
 */

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "pigeon.h"

int main() {

  std::string fname = "../tests/data/pub1.txt";
  std::string P = "Its_weird_that_the_animaniacs_are_on_tv_again";
  int mm = 1;

  std::string T = "ABCDEFG";
  kmerMap outMap = text_to_kmer_map(T,4);
  for(kmerMap::iterator it = outMap.begin(); it != outMap.end(); ++it){
    std::cout << it->first << " : { ";
    std::vector<int> indList = it->second;
    for(size_t i = 0; i < indList.size(); ++i){
      std::cout << indList[i] << " ";
    }
    std::cout << "}" << std::endl;
  }

  std::vector<Seed> outPart = partitionPattern(P, 6);
  std::cout << "Partition List:" << std::endl;
  for(size_t i = 0; i < outPart.size(); ++i){
    std::cout << "{ " << outPart[i].first << ", " << outPart[i].second << " }" << std::endl;
  }

  std::vector<int> output = approximate_search(fname, P, mm);

  std::cout << "Search results: " << std::endl;
  std::cout << "{ ";
  for(size_t i = 0; i < output.size(); ++i){
    std::cout  << output[i] << ", ";
  }
  std::cout << "}" << std::endl;

  


  return 0;
}
