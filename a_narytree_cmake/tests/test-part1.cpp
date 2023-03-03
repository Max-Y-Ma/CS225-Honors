#include <catch2/catch_test_macros.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "narytree.h"

/*
* Helper functions for basic tests
*/

void check_pmatch(NaryTree & strie, std::string P, std::vector<int> ans){
  std::vector<int> outList;

  outList = strie.patternMatch(P);

  std::sort (outList.begin(), outList.end());
  std::sort (ans.begin(), ans.end());

  REQUIRE(outList.size() == ans.size());

  for(size_t i = 0; i < ans.size(); ++i){
    if(outList[i]!=ans[i]){ 
      INFO("Your outList (when sorted) is incorrect at index: " + std::to_string(i) + "");
      REQUIRE(outList[i] == ans[i]);
    }
  }
}

void match_walk(NaryTree & strie, std::vector<char> ans){
  std::vector<char> lexW;
  
  strie.inLexOrder(lexW);

  REQUIRE(lexW.size() == ans.size());

  for(size_t i = 0; i < ans.size(); ++i){
    if(lexW[i]!=ans[i]){ 
      INFO("At index value " + std::to_string(i) + " your lexWalk was incorrect.");
      INFO("Check your printed tree for incorrect structure.");
      REQUIRE(lexW[i] == ans[i]);
    }
  }
  
}

/*
* Public test cases for trie construction (Total 35 points / weight 35)
*/

TEST_CASE("Tree 1 Constructed Correctly", "[weight=10]") {
  std::string T = "ABCDEFG";
  NaryTree myTree = build_trie(T);
  std::vector<char> ans = { 'A' , 'B' , 'C' , 'D' , 'E' , 'F' , 'G' , 'B' , 'C' , 'D' , 'E' ,\
   'F' , 'G' , 'C' , 'D' , 'E' , 'F' , 'G' , 'D' , 'E' , 'F' , 'G' , 'E' , 'F' , 'G' , 'F' , 'G' , 'G' };
  

  match_walk(myTree, ans);

}

TEST_CASE("Tree 1 correct height", "[weight=5]") {
  std::string T = "ABCDEFG";
  NaryTree myTree = build_trie(T);
  int ans = 7;
  
  int h = myTree.height();

  REQUIRE(h == ans);

}

TEST_CASE("Tree 2 Constructed Correctly", "[weight=10]") {
  std::string T = "BBABBABABBA";
  NaryTree myTree = build_trie(T);
  std::vector<char> ans = { 'A' , 'B' , 'A' , 'B' , 'B' , 'A' , 'B' , 'A' , 'B' , 'A' , 'B' ,\
   'B' , 'A' , 'B' , 'A' , 'B' , 'A' , 'B' , 'B' , 'A' , 'B' , 'A' , 'B' , 'A' , 'B' , 'B' ,\
    'A' , 'B' , 'A' , 'B' , 'A' , 'B' , 'B' , 'A' , 'B' , 'A' , 'B' , 'A' , 'B' , 'B' , 'A' };


  match_walk(myTree, ans);

}

TEST_CASE("Tree 2 correct height", "[weight=5]") {
  std::string T = "BBABBABABBA";
  NaryTree myTree = build_trie(T);
  int ans = 11;
  
  int h = myTree.height();

  REQUIRE(h == ans);

}

TEST_CASE("Tree 3 (Hard to visualize) Constructed Correctly", "[weight=2]") {
  std::string T = "zebras_playing_zylaphones";
  NaryTree myTree = build_trie(T);
  std::vector<char> ans = { '_' , 'p' , 'l' , 'a' , 'y' , 'i' , 'n' , 'g' , '_' ,\
   'z' , 'y' , 'l' , 'a' , 'p' , 'h' , 'o' , 'n' , 'e' , 's' , 'z' , 'y' , 'l' , 'a' ,\
    'p' , 'h' , 'o' , 'n' , 'e' , 's' , 'a' , 'p' , 'h' , 'o' , 'n' , 'e' , 's' , 's' ,\
     '_' , 'p' , 'l' , 'a' , 'y' , 'i' , 'n' , 'g' , '_' , 'z' , 'y' , 'l' , 'a' , 'p' ,\
      'h' , 'o' , 'n' , 'e' , 's' , 'y' , 'i' , 'n' , 'g' , '_' , 'z' , 'y' , 'l' , 'a' ,\
       'p' , 'h' , 'o' , 'n' , 'e' , 's' , 'b' , 'r' , 'a' , 's' , '_' , 'p' , 'l' , 'a' ,\
        'y' , 'i' , 'n' , 'g' , '_' , 'z' , 'y' , 'l' , 'a' , 'p' , 'h' , 'o' , 'n' , 'e' ,\
         's' , 'e' , 'b' , 'r' , 'a' , 's' , '_' , 'p' , 'l' , 'a' , 'y' , 'i' , 'n' , 'g' ,\
          '_' , 'z' , 'y' , 'l' , 'a' , 'p' , 'h' , 'o' , 'n' , 'e' , 's' , 's' , 'g' , '_' ,\
           'z' , 'y' , 'l' , 'a' , 'p' , 'h' , 'o' , 'n' , 'e' , 's' , 'h' , 'o' , 'n' , 'e' ,\
            's' , 'i' , 'n' , 'g' , '_' , 'z' , 'y' , 'l' , 'a' , 'p' , 'h' , 'o' , 'n' , 'e' ,\
             's' , 'l' , 'a' , 'p' , 'h' , 'o' , 'n' , 'e' , 's' , 'y' , 'i' , 'n' , 'g' , '_' ,\
              'z' , 'y' , 'l' , 'a' , 'p' , 'h' , 'o' , 'n' , 'e' , 's' , 'n' , 'e' , 's' , 'g' ,\
               '_' , 'z' , 'y' , 'l' , 'a' , 'p' , 'h' , 'o' , 'n' , 'e' , 's' , 'o' , 'n' , 'e' ,\
                's' , 'p' , 'h' , 'o' , 'n' , 'e' , 's' , 'l' , 'a' , 'y' , 'i' , 'n' , 'g' , '_' ,\
                 'z' , 'y' , 'l' , 'a' , 'p' , 'h' , 'o' , 'n' , 'e' , 's' , 'r' , 'a' , 's' , '_' ,\
                  'p' , 'l' , 'a' , 'y' , 'i' , 'n' , 'g' , '_' , 'z' , 'y' , 'l' , 'a' , 'p' , 'h' ,\
                   'o' , 'n' , 'e' , 's' , 's' , '_' , 'p' , 'l' , 'a' , 'y' , 'i' , 'n' , 'g' , '_' ,\
                    'z' , 'y' , 'l' , 'a' , 'p' , 'h' , 'o' , 'n' , 'e' , 's' , 'y' , 'i' , 'n' , 'g' ,\
                     '_' , 'z' , 'y' , 'l' , 'a' , 'p' , 'h' , 'o' , 'n' , 'e' , 's' , 'l' , 'a' , 'p' ,\
                      'h' , 'o' , 'n' , 'e' , 's' , 'z' , 'e' , 'b' , 'r' , 'a' , 's' , '_' , 'p' , 'l' ,\
                       'a' , 'y' , 'i' , 'n' , 'g' , '_' , 'z' , 'y' , 'l' , 'a' , 'p' , 'h' , 'o' , 'n' ,\
                        'e' , 's' , 'y' , 'l' , 'a' , 'p' , 'h' , 'o' , 'n' , 'e' , 's'};
  

  match_walk(myTree, ans);

}

TEST_CASE("Tree 3 (Hard to visualize) correct height", "[weight=3]") {
  std::string T = "zebras_playing_zylaphones";
  NaryTree myTree = build_trie(T);
  int ans = 25;
  
  int h = myTree.height();

  REQUIRE(h == ans);

}


/*
* Public test cases for trie pattern matching (Total 30 points / weight 30)
*/

TEST_CASE("Can find no match in tree", "[weight=5]") {
  
  NaryTree myTree;
  std::vector<int> ans;

  ans = {-1};
  check_pmatch(myTree,"ZZZ", ans);

  myTree.insert("ABCD", 0);
  myTree.insert("BCD", 1);
  myTree.insert("CD", 2);

  ans = {-1};
  check_pmatch(myTree,"ZZZ", ans);

  myTree.insert("ZZZ", 10);

  ans = {-1};
  check_pmatch(myTree,"good on you for reading these tests", ans);

}


TEST_CASE("Specific key search can find matching keys", "[weight=10]") {
  
  NaryTree myTree;
  std::vector<int> ans;

  myTree.insert("ABCD", 0);
  myTree.insert("BCD", 1);
  myTree.insert("CD", 2);

  ans = {0};
  check_pmatch(myTree, "ABCD", ans);

  myTree.insert("ZZZ", 10);

  ans = {10};
  check_pmatch(myTree,"ZZZ", ans);


  myTree.insert("BCD", 5);
  myTree.insert("BCD", 7);
  myTree.insert("BCD", 10);
  ans = {1, 5, 7, 10};
  check_pmatch(myTree,"BCD", ans);

}

TEST_CASE("Specific key search wont match substrings", "[weight=5]") {

  NaryTree myTree;
  std::vector<int> ans;

  myTree.insert("GGGG",0);

  ans = {-1};
  check_pmatch(myTree, "G", ans);
  check_pmatch(myTree, "GG", ans);
  check_pmatch(myTree, "GGG", ans);

  myTree.insert("TCGTAGTAGAC",5);
  check_pmatch(myTree, "CGTAGTAGAC", ans);
  check_pmatch(myTree, "TCGTA", ans);
  check_pmatch(myTree, "GTAG", ans);

}

TEST_CASE("Repetition Detection 1", "[weight=5]") {

  std::string T = "BBBBBBBBBB";
  NaryTree myTree = build_trie(T);
  std::vector<int> ans;

  ans = {0,1,2,3,4,5,6,7,8,9};
  check_pmatch(myTree, "B", ans);
  ans = {0,1,2,3,4,5,6,7,8};
  check_pmatch(myTree, "BB", ans);
  ans = {0,1,2,3,4,5,6,7};
  check_pmatch(myTree, "BBB", ans);

}

TEST_CASE("Repetition Detection 2", "[weight=5]") {

  std::string T = "ZGTATAGAGTATATGZGATGTAT";
  NaryTree myTree = build_trie(T);
  std::vector<int> ans;

  ans = { 2 , 9 , 11 , 20 };
  check_pmatch(myTree, "TAT", ans);
  ans = { 2 , 9 };
  check_pmatch(myTree, "TATA", ans);
  ans = {0,15};
  check_pmatch(myTree, "ZG", ans);

}