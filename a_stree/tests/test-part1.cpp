#include <catch2/catch_test_macros.hpp>

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "stree.h"

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

void match_walk(NaryTree & strie, std::vector<std::string> ans){
  std::vector<std::string> lexW;
  
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
* Public test cases for strie construction (Total 10 points / weight 10)
*/

TEST_CASE("Tree 1 Constructed Correctly", "[weight=3]") {
  std::string T = "ABCDEFG";
  NaryTree myTree = build_strie(T);
  std::vector<std::string> ans = { "$" , "A" , "B" , "C" , "D" , "E" , "F" , "G" , "$" , "B" \
  , "C" , "D" , "E" , "F" , "G" , "$" , "C" , "D" , "E" , "F" , "G" , "$" , "D" , "E" , "F" ,\
   "G" , "$" , "E" , "F" , "G" , "$" , "F" , "G" , "$" , "G" , "$" };
  

  match_walk(myTree, ans);

}

TEST_CASE("Tree 1 correct height", "[weight=2]") {
  std::string T = "ABCDEFG";
  NaryTree myTree = build_strie(T);
  int ans = 8;
  
  int h = myTree.height();

  REQUIRE(h == ans);

}

TEST_CASE("Tree 2 Constructed Correctly", "[weight=3]") {
  std::string T = "BBABBABABBA";
  NaryTree myTree = build_strie(T);
  std::vector<std::string> ans = { "$" , "A" , "$" , "B" , "A" , "B" , "B" , "A" , "$" , "B" ,\
   "A" , "$" , "B" , "A" , "B" , "B" , "A" , "$" , "B" , "A" , "$" , "B" , "A" , "B" , "B" ,\
    "A" , "$" , "B" , "A" , "$" , "B" , "A" , "B" , "B" , "A" , "$" , "B" , "A" , "$" , "B" ,\
     "A" , "B" , "B" , "A" , "$" , "B" , "A" , "B" , "A" , "B" , "B" , "A" , "$" };


  match_walk(myTree, ans);

}

TEST_CASE("Tree 2 correct height", "[weight=2]") {
  std::string T = "BBABBABABBA";
  NaryTree myTree = build_strie(T);
  int ans = 12;
  
  int h = myTree.height();

  REQUIRE(h == ans);

}

/*
* Public test cases for strie pattern matching (Total 25 points / weight 25)
*/

TEST_CASE("Can find no match in tree", "[weight=5]") {
  
  NaryTree myTree;
  std::vector<int> ans;

  ans = {-1};
  check_pmatch(myTree,"ZZZ", ans);

  myTree.insert("ABCD$", 0);
  myTree.insert("BCD$", 1);
  myTree.insert("CD$", 2);

  ans = {-1};
  check_pmatch(myTree,"ZZZ", ans);

  myTree.insert("ZZZ$", 10);

  ans = {-1};
  check_pmatch(myTree,"good on you for reading these tests", ans);

}


TEST_CASE("Specific key search can find matching keys", "[weight=5]") {
  
  NaryTree myTree;
  std::vector<int> ans;

  myTree.insert("ABCD$", 0);
  myTree.insert("BCD$", 1);
  myTree.insert("CD$", 2);

  ans = {0};
  check_pmatch(myTree, "ABCD", ans);

  myTree.insert("ZZZ$", 10);

  ans = {10};
  check_pmatch(myTree,"ZZZ", ans);


  myTree.insert("BCDA$", 5);
  myTree.insert("BCDB$", 7);
  myTree.insert("BCDC$", 10);
  ans = {1, 5, 7, 10};
  check_pmatch(myTree,"BCD", ans);

}

TEST_CASE("Search will match prefixes of suffixes.", "[weight=5]") {

  NaryTree myTree;
  std::vector<int> ans;

  myTree.insert("GGGG$",1212);

  // If you are confused by this, note the difference between *insert* and *build_strie*
  ans = {1212};
  check_pmatch(myTree, "G", ans);
  ans = {1212};
  check_pmatch(myTree, "GG", ans);
  ans = {1212};
  check_pmatch(myTree, "GGG", ans);

  myTree.insert("TCGTAGTAGAC$",5);
  ans = {-1};
  check_pmatch(myTree, "CGTAGTAGAC", ans);
  ans = {5};
  check_pmatch(myTree, "TCGTA", ans);
  ans = {-1};
  check_pmatch(myTree, "GTAG", ans);

}

TEST_CASE("Repetition Detection 1", "[weight=5]") {

  std::string T = "BBBBBBBBBB";
  NaryTree myTree = build_strie(T);
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
  NaryTree myTree = build_strie(T);
  std::vector<int> ans;

  ans = { 2 , 9 , 11 , 20 };
  check_pmatch(myTree, "TAT", ans);
  ans = { 2 , 9 };
  check_pmatch(myTree, "TATA", ans);
  ans = {0,15};
  check_pmatch(myTree, "ZG", ans);

}


/*
* Public test cases for strie to stree conversion (Total 15 points / weight 15)
*/

TEST_CASE("Trie to Tree I", "[weight=5]") {

  std::string T = "TCGATCGA";
  NaryTree myTree = build_strie(T);
  myTree.trie_to_tree();
  std::vector<std::string> ans = { "$" , "A" , "$" , "TCGA$" , "CGA" , "$" , "TCGA$" , "GA" , "$" , "TCGA$" , "TCGA" , "$" , "TCGA$"};

  match_walk(myTree, ans);

}

TEST_CASE("Trie to Tree II", "[weight=5]") {

  std::string T = "ABCDEF";
  NaryTree myTree = build_strie(T);
  myTree.trie_to_tree();
  std::vector<std::string> ans = { "$" , "ABCDEF$" , "BCDEF$" , "CDEF$" , "DEF$" , "EF$" , "F$"};

  match_walk(myTree, ans);

}

TEST_CASE("Trie to Tree III", "[weight=5]") {

  std::string T = "BBAABBAABBAAB";
  NaryTree myTree = build_strie(T);
  myTree.trie_to_tree();
  std::vector<std::string> ans = { "$" , "A" , "AB" , "$" , "BAAB" , "$" , "BAAB$" , "B" , "$" , "BAAB" , "$" , "BAAB$" , "B" , "$" ,\
   "AAB" , "$" , "BAAB" , "$" , "BAAB$" , "BAAB" , "$" , "BAAB" , "$" , "BAAB$"};

  match_walk(myTree, ans);

}

bool NaryTree::checkLeaves(){
  checkLeaves(root);
  return true;
}

void NaryTree::checkLeaves(Node* subRoot){
  if (subRoot->isLeaf()){
    /*
        int *p = &(subRoot->index);
        bool leafValue = false;
        if(p != NULL){
          leafValue = true;
        }
      */
        int nocheat = -12;
        int secretTest = subRoot->index;
        REQUIRE(secretTest != nocheat);
    } else {
      /*
      int *p = &(subRoot->index);
      bool leafValue = false;
      if(p != NULL){
        std::cout << subRoot->index << std::endl;
        leafValue = true;
      }
      */
      int nocheat = -12;
      int secretTest = subRoot->index;
      REQUIRE(secretTest == nocheat);

        std::map<std::string,Node*>::iterator it;
        for (it = subRoot->children.begin(); it != subRoot->children.end(); it++){
            checkLeaves(it->second);
        }
    }
}