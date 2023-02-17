#include <catch2/catch_test_macros.hpp>

#include <string>
#include <iostream>
#include <vector>

#include "zalg.h"

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

void matchzalgSearch(std::vector<int> output, std::vector<int> ans){
  for(unsigned i = 1; i < ans.size(); ++i){
    if(output[i]!=ans[i]){ 
      INFO("At index value: " + std::to_string(i) + " your zalg_search output was incorrect.");
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
* Public test cases for create Z array (50 points)
*/

TEST_CASE("All Z-values are correct 1", "[weight=10]") {
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

TEST_CASE("All Z-values are correct 2", "[weight=10]") {
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

TEST_CASE("Z-array computed efficiently.", "[weight=10]") {


  std::string P = "AAA";
  std::string T = "BAAAT";
  int ans_comps = 12; 
  int delta = 1;

  check_Zarray_efficiency(P,T,ans_comps,delta);

  P = "pattern";
  T = "this is a pattern that has a repeat pattern";
  ans_comps = 52; 
  delta = 2;

  check_Zarray_efficiency(P,T,ans_comps,delta);

}

TEST_CASE("Z-array computed efficiently 2", "[weight=10]") {


  std::string P = "CGACGA";
  std::string T = "CGCGCGCG";
  int ans_comps = 18; 
  int delta = 1;

  check_Zarray_efficiency(P,T,ans_comps,delta);

  P = "matters";
  T = "It matters that the third matters mattErs. It also may matteRs that this sentence also matters";
  ans_comps = 106; 
  delta = 4;

  check_Zarray_efficiency(P,T,ans_comps,delta);

  P = "Q is not found anywhere so even though this is really long it doesnt compare many chars";
  T = "It matters that the third matters mattErs. It also may matteRs that this sentence also matters";
  ans_comps = 181; 
  delta = 2;

  check_Zarray_efficiency(P,T,ans_comps,delta);

}

TEST_CASE("Z-array computed semi-efficiently", "[weight=10]") {


  std::string P = "CGACGA";
  std::string T = "CGCGCGCG";
  int ans_comps = 18; 
  int delta = ans_comps / 5.0 ;

  check_Zarray_efficiency(P,T,ans_comps,delta);

  P = "matters";
  T = "It matters that the third matters mattErs. It also may matteRs that this sentence also matters";
  ans_comps = 106; 
  delta = ans_comps / 5.0;

  check_Zarray_efficiency(P,T,ans_comps,delta);

  P = "Q is not found anywhere so even though this is really long it doesnt compare many chars";
  T = "It matters that the third matters mattErs. It also may matteRs that this sentence also matters";
  ans_comps = 181; 
  delta = ans_comps / 5.0;

  check_Zarray_efficiency(P,T,ans_comps,delta);

}