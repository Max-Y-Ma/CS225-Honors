#include <catch2/catch_test_macros.hpp>

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include "sarray.h"


/*
* Helper functions for basic tests
*/

void matchSarray(std::vector<int> output, std::vector<int> ans){

  REQUIRE(output.size() == ans.size());

  for(size_t i = 0; i < ans.size(); ++i){
    if(output[i]!=ans[i]){ 
      INFO("At index value: " + std::to_string(i) + " your array was incorrect.");
      REQUIRE(output[i] == ans[i]);
    }
  }
}


void matchArray(std::vector<int> output, std::vector<int> ans){
  std::sort(output.begin(),output.end()); 
  std::sort(ans.begin(),ans.end()); 

  REQUIRE(output.size() == ans.size());

  for(size_t i = 0; i < ans.size(); ++i){
    if(output[i]!=ans[i]){ 
      INFO("At index value: " + std::to_string(i) + " your array (when sorted) was incorrect.");
      REQUIRE(output[i] == ans[i]);
    }
  }
}


/*
* Public test cases for build_sarray (Total 25 points / weight 25)
*/

TEST_CASE("Sarray Correct Public Test 1", "[weight=5]") {
  std::string T = "BABAAAB";
  std::vector<int> ans = { 7, 3, 4, 5, 1, 6, 2, 0};

  std::vector<int> sarray = build_sarray(T);

  matchSarray(sarray,ans);
}

TEST_CASE("Sarray Correct Public Test 2", "[weight=5]") {
  std::string T = "ABCDEFG";
  std::vector<int> ans = { 7, 0, 1, 2, 3, 4, 5, 6};

  std::vector<int> sarray = build_sarray(T);

  matchSarray(sarray,ans);
}


TEST_CASE("Sarray Correct Public Test 3", "[weight=5]") {
  std::string T = "BBABBABABBA";
  std::vector<int> ans = { 11, 10, 5, 7, 2, 9, 4, 6, 1, 8, 3, 0};

  std::vector<int> sarray = build_sarray(T);

  matchSarray(sarray,ans);
}

TEST_CASE("Sarray Correct Public Test 4 (English text)", "[weight=5]") {
  std::string T = "beep_beep_ima_sheep";
  std::vector<int> ans = { 19, 4, 9, 13, 12, 0, 5, 16, 1, 6, 17,\
   2, 7, 15, 10, 11, 18, 3, 8, 14 };

  std::vector<int> sarray = build_sarray(T);

  matchSarray(sarray,ans);
}

TEST_CASE("Sarray Correct Public Test 5 (Upper and Lower Case)", "[weight=5]") {
  std::string T = "Phnglui_mglwnafh_Cthulhu_Rlyeh_wgahnagl_fhtagn";
  std::vector<int> ans = { 46, 17, 0, 25, 16, 24, 39, 7, 30, 13, 36, 43, 33,\
   28, 14, 40, 32, 37, 3, 9, 44, 15, 29, 34, 1, 41, 22, 19, 6, 38, 21, 4, 10,\
    26, 8, 45, 12, 35, 2, 42, 18, 23, 5, 20, 31, 11, 27};

  std::vector<int> sarray = build_sarray(T);

  matchSarray(sarray,ans);
}

/*
* Public test cases for sarray_search (Total 25 points / weight 25)
*/

TEST_CASE("Sarray Search can handle no match", "[weight=5]") {
  std::string P = "BABAAAB";
  std::string T = "BBBBBBBBBBBBBBBBBBBBB";
  std::vector<int> sarray = build_sarray(T);
  std::vector<int> ans = {-1};
  std::vector<int> outList;

  outList = sarray_search(P, T, sarray);

  matchArray(outList,ans);

  P = "AA";
  T = "BBBBB"; 
  sarray = build_sarray(T);
  outList.clear();
  ans = {-1};

  outList = sarray_search(P, T, sarray);

  matchArray(outList,ans);

  P = "AA";
  T = "BBBB"; 
  sarray = build_sarray(T);
  ans = {-1};
  outList.clear();

  outList = sarray_search(P, T, sarray);

  matchArray(outList,ans);

  P = "BA";
  T = "BB"; 
  sarray = build_sarray(T);
  ans = {-1};
  outList.clear();

  outList = sarray_search(P, T, sarray);
  matchArray(outList,ans);
}


TEST_CASE("Sarray Search values are correct Public 1", "[weight=5]") {
  std::string P = "B";
  std::string T = "BBBBBBBBBB";
  std::vector<int> ans = {0,1,2,3,4,5,6,7,8,9};
  std::vector<int> sarray = build_sarray(T);
  std::vector<int> outList;

  outList = sarray_search(P, T, sarray);
  matchArray(outList,ans);

  P = "BB";
  ans = {0,1,2,3,4,5,6,7,8};
  outList.clear(); // delete outlist contents without deleting object

  outList = sarray_search(P, T, sarray);
  matchArray(outList,ans);

  P = "BBB";
  ans = {0,1,2,3,4,5,6,7};
  outList.clear(); // delete outlist contents without deleting object

  outList = sarray_search(P, T, sarray);
  matchArray(outList,ans);
}


TEST_CASE("Sarray Search values are correct Public 2", "[weight=5]") {
  std::string P = "eep";
  std::string T = "beep_beep_ima_sheep";
  std::vector<int> sarray = build_sarray(T);
  std::vector<int> ans = {1,6,16};
  std::vector<int> outList;
  
  outList = sarray_search(P, T, sarray);

  matchArray(outList,ans);


  P = "pattern";
  T = "this is a pattern that has a repeat pattern";
  sarray = build_sarray(T);
  ans= {10,36};
  outList.clear(); // delete outlist contents without deleting object

  outList = sarray_search(P, T, sarray);
  matchArray(outList,ans);
}

TEST_CASE("Sarray Search values are correct Public 3", "[weight=5]") {
  std::string P = "TAT";
  std::string T = "ZGTATAGAGTATATGZGATGTAT";
  std::vector<int> sarray = build_sarray(T);
  std::vector<int> ans = { 2 , 9 , 11 , 20 };
  std::vector<int> outList;
  
  outList = sarray_search(P, T, sarray);

  matchArray(outList,ans);


  P = "TATA";
  ans = { 2 , 9 };
  outList.clear(); // delete outlist contents without deleting object

  outList = sarray_search(P, T, sarray);
  matchArray(outList,ans);

  P = "ZG";
  ans = { 0 , 15 };
  outList.clear(); // delete outlist contents without deleting object

  outList = sarray_search(P, T, sarray);
  matchArray(outList,ans);
}

TEST_CASE("Sarray Search values are correct Public 4", "[weight=5]") {
  std::string P = "TCG";
  std::string T = "TCGATGATCGATCGATCGAAATCGATCGATCGCTCGATCGCTCGATGCTAGCTA";
  std::vector<int> ans = { 33, 0, 41, 29, 37, 25, 21, 7, 11, 15};
  std::vector<int> sarray = build_sarray(T);
  std::vector<int> outList;

  outList = sarray_search(P, T, sarray);
  matchArray(outList,ans);

}