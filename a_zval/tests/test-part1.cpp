#include <catch2/catch_test_macros.hpp>

#include <string>
#include <iostream>
#include <vector>

#include "zval.h"

/*
* Helper functions for basic tests
*/

void matchArray(int* output, std::vector<int> ans, int len){
  for(int i = 1; i < len; ++i){
    if(output[i]!=ans[i]){ 
      INFO("At index value " + std::to_string(i) + " your z-array was incorrect.");
      REQUIRE(output[i] == ans[i]);
    }
  }
}

void matchzvalSearch(std::vector<int> output, std::vector<int> ans){
  for(unsigned i = 1; i < ans.size(); ++i){
    if(output[i]!=ans[i]){ 
      INFO("At index value: " + std::to_string(i) + " your zval_search output was incorrect.");
      REQUIRE(output[i] == ans[i]);
    }
  }
}


void testZarray(std::string P, std::string T, std::vector<int> ans){
  std::string S = P + "$" + T;
  int *zarr = new int[S.length()];

  create_zarray(S, zarr);
  matchArray(zarr, ans, S.length());
  
  delete[] zarr;

}

void check_Zarray_efficiency(std::string P, std::string T, int ans, int delta){
  std::string S = P + "$" + T;
  int *zarr = new int[S.length()];

  int charComps = create_zarray(S, zarr);

  REQUIRE(ans - delta <= charComps);
  REQUIRE(charComps <= ans + delta);
  
  delete[] zarr;

}

/*
* Public test cases for left to right scan (10 points)
*/

TEST_CASE("Scan produces correct character count 1", "[weight=2]") {
  std::string P = "AAA";
  std::string T = "BAAAT";
  std::pair<int, int> ans(1,0);
  std::pair<int, int> out = lr_scan(P, T);

  REQUIRE(out.first == ans.first);

  P = "abcdefg";
  T = "abcd efg";
  ans = std::make_pair(5,4);
  out = lr_scan(P, T);

  
  REQUIRE(out.first == ans.first);
}

TEST_CASE("Scan produces correct value 1", "[weight=2]") {
  std::string P = "AAA";
  std::string T = "BAAAT";
  std::pair<int, int> ans(1,0);
  std::pair<int, int> out = lr_scan(P, T);

  REQUIRE(out.second == ans.second);

  P = "abcdefg";
  T = "abcd efg";
  ans = std::make_pair(5,4);
  out = lr_scan(P, T);
  
  REQUIRE(out.second == ans.second);
}

TEST_CASE("Scan produces correct character count 2", "[weight=3]") {
  std::string P = "AAA";
  std::string T = "AAA";
  std::pair<int, int> ans(3,3);
  std::pair<int, int> out = lr_scan(P, T);

  REQUIRE(out.first == ans.first);

  P = "P is short";
  T = "P is short and T is long";
  ans = std::make_pair(10, 10);
  out = lr_scan(P, T);
  
  REQUIRE(out.first == ans.first);
}

TEST_CASE("Scan produces correct value 2", "[weight=3]") {
    std::string P = "AAA";
  std::string T = "AAA";
  std::pair<int, int> ans(3,3);
  std::pair<int, int> out = lr_scan(P, T);

  REQUIRE(out.second == ans.second);

  P = "P is short";
  T = "P is short and T is long";
  ans = std::make_pair(10, 10);
  out = lr_scan(P, T);
  
  REQUIRE(out.second == ans.second);
}

/*
* Public test cases for create Z array (20 points)
*/

TEST_CASE("All Z-values are correct 1", "[weight=5]") {
  std::string P = "AAA";
  std::string T = "BAAAT";
  std::vector<int> ans = {0,2,1,0,0,3,2,1,0};
  testZarray(P,T, ans);


  P = "pattern";
  T = "this is a pattern that has a repeat pattern";
  ans = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,\
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0};
  testZarray(P,T, ans);
}

TEST_CASE("All Z-values are correct 2", "[weight=5]") {
  std::string P = "AAA";
  std::string T = "BAAAT";
  std::vector<int> ans = {0,2,1,0,0,3,2,1,0};
  testZarray(P,T, ans);


  P = "matters";
  T = "It matters that the third matters mattErs. It also may matteRs that this sentence also matters";
  ans = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,\
   0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 5,\
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0,\
     0, 0, 0, 0, 0};
  testZarray(P,T, ans);
}

TEST_CASE("Z-array computed efficiently.", "[weight=5]") {


  std::string P = "AAA";
  std::string T = "BAAAT";
  int ans_comps = 17; 
  int delta = 0;

  check_Zarray_efficiency(P,T,ans_comps,delta);

  P = "pattern";
  T = "this is a pattern that has a repeat pattern";
  ans_comps = 64; 
  delta = 0;

  check_Zarray_efficiency(P,T,ans_comps,delta);

}

TEST_CASE("Z-array computed efficiently 2", "[weight=5]") {


  std::string P = "CGACGA";
  std::string T = "CGCGCGCG";
  int ans_comps = 24; 
  int delta = 0;

  check_Zarray_efficiency(P,T,ans_comps,delta);

  P = "matters";
  T = "It matters that the third matters mattErs. It also may matteRs that this sentence also matters";
  ans_comps = 132; 
  delta = 0;

  check_Zarray_efficiency(P,T,ans_comps,delta);

  P = "Q is not found anywhere so even though this is really long it doesnt compare many chars";
  T = "It matters that the third matters mattErs. It also may matteRs that this sentence also matters";
  ans_comps = 181; 
  delta = 0;

  check_Zarray_efficiency(P,T,ans_comps,delta);

}

/*
* Public test cases for search Z array (20 points)
*/
TEST_CASE("Output vector is correctly sized.", "[weight=5]") {


  std::string P = "AAA";
  std::string T = "BAAAT";

  std::vector<int> outVec = zval_search(P,T);

  REQUIRE(outVec.size() == 1);

  P = "pattern";
  T = "this is a pattern that has a repeat pattern";
  
  outVec = zval_search(P,T);

  REQUIRE(outVec.size() == 2);
}

TEST_CASE("Output vector is correct.", "[weight=5]") {
  std::string P = "AAA";
  std::string T = "BAAAT";
  std::vector<int> ans = {1};

  std::vector<int> outVec = zval_search(P,T);

  REQUIRE(outVec.size() == ans.size());
  matchzvalSearch(outVec,ans);

  P = "pattern";
  T = "this is a pattern that has a repeat pattern";
  ans = {10,36};
  outVec = zval_search(P,T);

  REQUIRE(outVec.size() == ans.size());
  matchzvalSearch(outVec,ans);

  P = "matters";
  T = "It matters that the third matters mattErs. It also may matteRs that this sentence also matters";
  ans = {3,26,87};

  outVec = zval_search(P,T);
  REQUIRE(outVec.size() == ans.size());
  matchzvalSearch(outVec,ans);
}

TEST_CASE("Output vector is correct 2", "[weight=5]") {
  std::string P = "CGC";
  std::string T = "CGCGCGCG";
  std::vector<int> ans = {0,2,4};

  std::vector<int> outVec = zval_search(P,T);

  REQUIRE(outVec.size() == ans.size());
  matchzvalSearch(outVec,ans);

  P = "AaaA";
  T = "caaaaapitalization mAaaAtters AaaAaaA";
  ans = {20, 30, 33};
  outVec = zval_search(P,T);

  REQUIRE(outVec.size() == ans.size());
  matchzvalSearch(outVec,ans);
}

TEST_CASE("Output vector handles no match.", "[weight=5]") {


  std::string P = "zebras";
  std::string T = "this is the story of a text that has no match";
  std::vector<int> ans = {-1};

  std::vector<int> outVec = zval_search(P,T);

  REQUIRE(outVec.size() == ans.size());
  matchzvalSearch(outVec,ans);

}
