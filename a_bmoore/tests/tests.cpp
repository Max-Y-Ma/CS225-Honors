#include <catch2/catch_test_macros.hpp>

#include <string>
#include <iostream>
#include <vector>

#include "bmoore.h"

/*
* Helper functions for basic tests
*/

void matchArray(std::vector<std::vector<int>> output, std::vector<std::vector<int>> ans){
  //std::cout << output.size() << std::endl;
  //std::cout << ans.size() << std::endl;
  REQUIRE(output.size() == ans.size());

  for(int i = 0; i < (int) ans.size(); ++i){
    REQUIRE(output[i].size() == ans[i].size());

    for(int j = 0; j < (int) ans[i].size(); ++j){
      //std::cout << output[i].size() << std::endl;
      //std::cout << ans[i].size() << std::endl;
      if(output[i][j]!=ans[i][j]){ 
        //std::cout << output[i][j] << std::endl;
        INFO("At bcarray[" + std::to_string(i) + "]["+ std::to_string(j) +"] your skip value was incorrect.");
        REQUIRE(output[i][j] == ans[i][j]);
      }
    }
  }
}

void matchSearch(std::vector<int> output, std::vector<int> ans){
  for(int i = 0; i < (int) ans.size(); ++i){
    if(output.size() != ans.size()){
      INFO("Output size (" + std::to_string(output.size()) + ") does not match ans size (" + std::to_string(ans.size()) + ")");
    }
    REQUIRE(output.size() == ans.size());
    if(output[i]!=ans[i]){ 
      INFO("At index value: " + std::to_string(i) + " your bmoore_search output was incorrect.");
      REQUIRE(output[i] == ans[i]);
    }
  }
}


/*
* Public test cases for prep_bc_array (25 Points)
*/

TEST_CASE("All skip values are correct (2 letter alphabet)", "[weight=10]") {
  std::string alpha = "AB";
  std::string P = "BABAAAB";
  std::vector<std::vector<int>> ans = { { 0, 1, 0, 1, 0, 0, 0}, \
  { 0, 0, 1, 0, 1, 2, 3} };

  std::vector<std::vector<int>> bc_array = prep_bc_array(P, alpha);

  matchArray(bc_array,ans);

  alpha = "AB";
  P = "AA";
  ans = { { 0, 0}, { 0, 1} };

  bc_array = prep_bc_array(P, alpha);

  matchArray(bc_array,ans);
}


TEST_CASE("All skip values are correct (4 letter alphabet)", "[weight=10]") {
  std::string alpha = "ACGT";
  std::string P = "CC";
  std::vector<std::vector<int>> ans = { { 0, 1}, \
{ 0, 0}, \
{ 0, 1}, \
{ 0, 1} };


  std::vector<std::vector<int>> bc_array = prep_bc_array(P, alpha);

  matchArray(bc_array,ans);

  alpha = "ACGT";
  P = "TTTTT";
  ans = { { 0, 1, 2, 3, 4}, \
{ 0, 1, 2, 3, 4}, \
{ 0, 1, 2, 3, 4}, \
{ 0, 0, 0, 0, 0} };


  bc_array = prep_bc_array(P, alpha);

  matchArray(bc_array,ans);
}


TEST_CASE("All skip values are correct (27 letter alphabet)", "[weight=5]") {
  std::string alpha = "abcdefghijklmnopqrstuvwxyz ";
  std::string P = "eep";
  std::vector<std::vector<int>> ans = { { 0, 1, 2}, \
{ 0, 1, 2}, \
{ 0, 1, 2}, \
{ 0, 1, 2}, \
{ 0, 0, 0}, \
{ 0, 1, 2}, \
{ 0, 1, 2}, \
{ 0, 1, 2}, \
{ 0, 1, 2}, \
{ 0, 1, 2}, \
{ 0, 1, 2}, \
{ 0, 1, 2}, \
{ 0, 1, 2}, \
{ 0, 1, 2}, \
{ 0, 1, 2}, \
{ 0, 1, 2}, \
{ 0, 1, 2}, \
{ 0, 1, 2}, \
{ 0, 1, 2}, \
{ 0, 1, 2}, \
{ 0, 1, 2}, \
{ 0, 1, 2}, \
{ 0, 1, 2}, \
{ 0, 1, 2}, \
{ 0, 1, 2}, \
{ 0, 1, 2}, \
{ 0, 1, 2} };

  std::vector<std::vector<int>> bc_array = prep_bc_array(P, alpha);

  matchArray(bc_array,ans);

  P = "pattern";
  ans = { { 0, 1, 0, 1, 2, 3, 4}, \
{ 0, 1, 2, 3, 4, 5, 6}, \
{ 0, 1, 2, 3, 4, 5, 6}, \
{ 0, 1, 2, 3, 4, 5, 6}, \
{ 0, 1, 2, 3, 4, 0, 1}, \
{ 0, 1, 2, 3, 4, 5, 6}, \
{ 0, 1, 2, 3, 4, 5, 6}, \
{ 0, 1, 2, 3, 4, 5, 6}, \
{ 0, 1, 2, 3, 4, 5, 6}, \
{ 0, 1, 2, 3, 4, 5, 6}, \
{ 0, 1, 2, 3, 4, 5, 6}, \
{ 0, 1, 2, 3, 4, 5, 6}, \
{ 0, 1, 2, 3, 4, 5, 6}, \
{ 0, 1, 2, 3, 4, 5, 6}, \
{ 0, 1, 2, 3, 4, 5, 6}, \
{ 0, 0, 1, 2, 3, 4, 5}, \
{ 0, 1, 2, 3, 4, 5, 6}, \
{ 0, 1, 2, 3, 4, 5, 0}, \
{ 0, 1, 2, 3, 4, 5, 6}, \
{ 0, 1, 2, 0, 0, 1, 2}, \
{ 0, 1, 2, 3, 4, 5, 6}, \
{ 0, 1, 2, 3, 4, 5, 6}, \
{ 0, 1, 2, 3, 4, 5, 6}, \
{ 0, 1, 2, 3, 4, 5, 6}, \
{ 0, 1, 2, 3, 4, 5, 6}, \
{ 0, 1, 2, 3, 4, 5, 6}, \
{ 0, 1, 2, 3, 4, 5, 6} };

  bc_array = prep_bc_array(P, alpha);

  matchArray(bc_array,ans);
}

/*
* Public test cases for bc_search (30 Points)
*/

TEST_CASE("Search values are correct (2 letter)", "[weight=4]") {
  std::string alpha = "AB";
  std::string P = "BABAAAB";
  std::string T = "BBBBBBBBBBBBBBBBBBBBB";
  std::vector<int> ans = {-1};
  std::vector<int> outList;

  bmoore_search(P, T, alpha, outList);

  matchSearch(outList,ans);

  alpha = "AB";
  P = "AA";
  T = "BBBBB"; // check edge case
  outList.clear();
  ans = {-1};

  bmoore_search(P, T, alpha, outList);

  matchSearch(outList,ans);

  alpha = "AB";
  P = "AA";
  T = "BBBB"; // check edge case
  ans = {-1};
  outList.clear();

  bmoore_search(P, T, alpha, outList);
  matchSearch(outList,ans);

  alpha = "AB";
  P = "BA";
  T = "BBBBBA"; // check edge case
  ans = {4};
  outList.clear();

  bmoore_search(P, T, alpha, outList);
  matchSearch(outList,ans);
}


TEST_CASE("Search values are correct (4 letter alphabet)", "[weight=3]") {

  std::string alpha = "ACGT";
  std::string P = "CC";
  std::string T = "CTTA";
  std::vector<int> ans = {-1};
  std::vector<int> outList;

  bmoore_search(P, T, alpha, outList);
  matchSearch(outList,ans);

  alpha = "ACGT";
  P = "TTTTT";
  T = "CTTTTTTA";
  ans = {1,2};
  outList.clear(); // delete outlist contents without deleting object

  bmoore_search(P, T, alpha, outList);
  matchSearch(outList,ans);
}


TEST_CASE("Search values are correct (27 letter alphabet)", "[weight=3]") {
  std::string alpha = "abcdefghijklmnopqrstuvwxyz ";
  std::string P = "eep";
  std::string T = "beep beep ima sheep";
  std::vector<int> ans = {1,6,16};
  std::vector<int> outList;
  

  bmoore_search(P, T, alpha, outList);
  matchSearch(outList,ans);

  

  P = "pattern";
  T = "this is a pattern that has a repeat pattern";
  ans= {10,36};
  outList.clear(); // delete outlist contents without deleting object

  bmoore_search(P, T, alpha, outList);
  matchSearch(outList,ans);
}

TEST_CASE("Total skips are correct (2 letter)", "[weight=5]") {
  std::string alpha = "AB";
  std::string P = "BABAAAB";
  std::string T = "BBBBBBBBBBBBBBBBBBBBB";
  int ans = 10;
  std::vector<int> outList;

  int skips = bmoore_search(P, T, alpha, outList);

  REQUIRE(skips == ans);

  alpha = "AB";
  P = "AA";
  T = "BBBBBB"; // check edge case
  outList.clear();
  ans = 2;

  skips = bmoore_search(P, T, alpha, outList);

  REQUIRE(skips == ans);

  alpha = "AB";
  P = "AA";
  T = "BBBB"; // check edge case
  ans = 1;
  outList.clear();

  alpha = "AB";
  P = "AA";
  T = "BBBBB"; // check edge case
  ans = 2;
  outList.clear();

  alpha = "AB";
  P = "AA";
  T = "BBBBBB"; // check edge case
  ans = 2;
  outList.clear();

  skips = bmoore_search(P, T, alpha, outList);
  REQUIRE(skips == ans);

  alpha = "AB";
  P = "BA";
  T = "BBBBBA"; // check edge case
  ans = 0;
  outList.clear();

  skips = bmoore_search(P, T, alpha, outList);
  REQUIRE(skips == ans);

  P = "AAA";
  T = "BBBBBBBAABBAAABBA";
  ans = 8;
  outList.clear(); // delete outlist contents without deleting object

  skips = bmoore_search(P, T, alpha, outList);
  REQUIRE(skips == ans);
}

TEST_CASE("Edge case special cases (Formerly private test)", "[weight=5]"){
  std::string alpha = "AB";
  std::string P = "AAA";
  std::string T = "BBBB";
  int ans = 1;
  std::vector<int> outList;

  int skips = bmoore_search(P, T, alpha, outList);
  REQUIRE(skips == ans);


  alpha = "TCGA";
  P = "CCCT";
  T = "AAAAAA";
  ans = 2;

  outList.clear();

  skips = bmoore_search(P, T, alpha, outList);
  REQUIRE(skips == ans);


}

TEST_CASE("Total skips are correct (4 letter alphabet)", "[weight=5]") {

  std::string alpha = "ACGT";
  std::string P = "CC";
  std::string T = "CTTA";
  int ans = 1;
  std::vector<int> outList;

  int skips = bmoore_search(P, T, alpha, outList);
  REQUIRE(skips == ans);

  alpha = "ACGT";
  P = "TTTTT";
  T = "CTTTTTTA";
  ans = 0;
  outList.clear(); // delete outlist contents without deleting object

  skips = bmoore_search(P, T, alpha, outList);
  REQUIRE(skips == ans);
}


TEST_CASE("Total skips are correct (27 letter alphabet)", "[weight=5]") {
  std::string alpha = "abcdefghijklmnopqrstuvwxyz ";
  std::string P = "eep";
  std::string T = "beep beep ima sheep";
  int ans = 8;
  std::vector<int> outList;
  

  int skips = bmoore_search(P, T, alpha, outList);
  REQUIRE(skips == ans);

  

  P = "pattern";
  T = "this is a pattern that has a repeat pattern";
  ans= 26;
  outList.clear(); // delete outlist contents without deleting object

  skips = bmoore_search(P, T, alpha, outList);
  REQUIRE(skips == ans);
}