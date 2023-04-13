#include <catch2/catch_test_macros.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include "pigeon.h"

/*
* Helper functions for basic tests
*/


void matchString(std::string & output, std::string & ans){

  REQUIRE(output.size() == ans.size());

  for(size_t i = 0; i < ans.size(); ++i){
    if(output[i]!=ans[i]){ 
      INFO("At index value: " + std::to_string(i) + " your string was incorrect.");
      REQUIRE(output[i] == ans[i]);
    }
  }
}

void matchVect(std::vector<int> & output, std::vector<int> & ans){

  REQUIRE(output.size() == ans.size());

  for(size_t i = 0; i < ans.size(); ++i){
    if(output[i]!=ans[i]){ 
      INFO("At index value: " + std::to_string(i) + " your vector was incorrect.");
      REQUIRE(output[i] == ans[i]);
    }
  }
}

void matchMap(kmerMap & output, kmerMap & ans){

  REQUIRE(output.size() == ans.size());

  for(kmerMap::iterator it = ans.begin(); it != ans.end(); it++){
    std::string key = it->first;
    std::vector<int> ans_vec = it->second;

    if(output.count(key) <= 0){
      INFO("kmerMap missing key: " + key);
    }
    REQUIRE(output.count(key) > 0);
    std::vector<int> out_vec = output[key];
    
    matchVect(out_vec, ans_vec);
  }
}

void matchSeed(std::vector<Seed> & output, std::vector<Seed> & ans){

  REQUIRE(output.size() == ans.size());

  std::sort(output.begin(),output.end()); 
  std::sort(ans.begin(),ans.end()); 

  for(size_t i = 0; i < ans.size(); ++i){
    if(output[i].first!=ans[i].first){ 
      INFO("At index value: " + std::to_string(i) + " your string was incorrect.");
      REQUIRE(output[i].first == ans[i].first);
    }
    if(output[i].second!=ans[i].second){ 
      INFO("At index value: " + std::to_string(i) + " your index value was incorrect.");
      REQUIRE(output[i].second == ans[i].second);
    }
  }
}

/*
* Public test cases for text_to_kmer_map (Total 15 points / weight 15)
*/

TEST_CASE("Text to Kmer Map Public Test 1", "[weight=5]") {
  std::string T = "BABAAAB";
  int k = 2;

  kmerMap ans;
  ans["BA"] = {0, 2};
  ans["AB"] = {1, 5};
  ans["AA"] = {3, 4};

  kmerMap output = text_to_kmer_map(T, k);
  matchMap(output,ans);

  ans.clear();

  k=3;
  ans["AAA"] = { 3};
  ans["AAB"] = { 4};
  ans["BAA"] = { 2};
  ans["ABA"] = { 1};
  ans["BAB"] = { 0};
  output = text_to_kmer_map(T, k);
  matchMap(output,ans);
}

TEST_CASE("Text to Kmer Map Public Test 2", "[weight=5]") {
  std::string T = "beep_beep_ima_sheep";
  int k = 4;

  kmerMap ans;
  ans["heep"] = { 15};
  ans["_she"] = { 13};
  ans["a_sh"] = { 12};
  ans["ma_s"] = { 11};
  ans["p_be"] = { 3};
  ans["ima_"] = { 10};
  ans["eep_"] = { 1, 6};
  ans["p_im"] = { 8};
  ans["_bee"] = { 4};
  ans["shee"] = { 14};
  ans["beep"] = { 0, 5};
  ans["_ima"] = { 9};
  ans["ep_b"] = { 2};
  ans["ep_i"] = { 7};

  kmerMap output = text_to_kmer_map(T, k);
  matchMap(output,ans);

  ans.clear();

  k=1;
  ans["h"] = { 15};
  ans["s"] = { 14};
  ans["m"] = { 11};
  ans["p"] = { 3, 8, 18};
  ans["a"] = { 12};
  ans["i"] = { 10};
  ans["e"] = { 1, 2, 6, 7, 16, 17};
  ans["_"] = { 4, 9, 13};
  ans["b"] = { 0, 5};
  output = text_to_kmer_map(T, k);
  matchMap(output,ans);
}

TEST_CASE("Text to Kmer Map Public Test 3", "[weight=5]") {
  std::string T = "Phnglui_mglwnafh_Cthulhu_Rlyeh_wgahnagl_fhtagn";
  int k = 6;

  kmerMap ans;
  ans["l_fhta"] = { 38};
  ans["agl_fh"] = { 36};
  ans["ahnagl"] = { 33};
  ans["_wgahn"] = { 30};
  ans["h_wgah"] = { 29};
  ans["eh_wga"] = { 28};
  ans["yeh_wg"] = { 27};
  ans["lyeh_w"] = { 26};
  ans["u_Rlye"] = { 23};
  ans["hu_Rly"] = { 22};
  ans["gl_fht"] = { 37};
  ans["Rlyeh_"] = { 25};
  ans["lhu_Rl"] = { 21};
  ans["nglui_"] = { 2};
  ans["ulhu_R"] = { 20};
  ans["h_Cthu"] = { 15};
  ans["gahnag"] = { 32};
  ans["i_mglw"] = { 6};
  ans["nafh_C"] = { 12};
  ans["fhtagn"] = { 40};
  ans["glwnaf"] = { 9};
  ans["afh_Ct"] = { 13};
  ans["hulhu_"] = { 19};
  ans["wnafh_"] = { 11};
  ans["thulhu"] = { 18};
  ans["lui_mg"] = { 4};
  ans["hnagl_"] = { 34};
  ans["lwnafh"] = { 10};
  ans["fh_Cth"] = { 14};
  ans["_mglwn"] = { 7};
  ans["glui_m"] = { 3};
  ans["_fhtag"] = { 39};
  ans["nagl_f"] = { 35};
  ans["_Rlyeh"] = { 24};
  ans["ui_mgl"] = { 5};
  ans["hnglui"] = { 1};
  ans["mglwna"] = { 8};
  ans["wgahna"] = { 31};
  ans["Cthulh"] = { 17};
  ans["_Cthul"] = { 16};
  ans["Phnglu"] = { 0};

  kmerMap output = text_to_kmer_map(T, k);
  matchMap(output,ans);
}

/*
* Public test cases for partitionPattern (Total 15 points / weight 15)
*/
TEST_CASE("partitionPattern Public Test 1", "[weight=5]") {
  std::string P = "BABAAAB";
  int np = 4;

  std::vector<std::string> p1 = { "BA" , "BA" , "AA" , "B" };

  std::vector<int> p2 = { 0, 2, 4, 6 };

  std::vector<Seed> ans;

  for(size_t i = 0; i < p1.size(); i++){
    ans.push_back(std::make_pair(p1[i],p2[i]));
  }

  std::vector<Seed> output = partitionPattern(P, np);
  matchSeed(output,ans);

  ans.clear();

  np=1;
  p1 = {"BABAAAB"};
  p2 = {0};
  for(size_t i = 0; i < p1.size(); i++){
    ans.push_back(std::make_pair(p1[i],p2[i]));
  }

  output = partitionPattern(P, np);
  matchSeed(output,ans);
  
}

TEST_CASE("partitionPattern Public Test 2", "[weight=5]") {
  std::string P = "what_if_our_partition_was_as_long_as_a_text";
  int np = 6;

  std::vector<std::string> p1 = { "what_if_", "our_par", "tition_", "was_as_", "long_as", "_a_text"};
  std::vector<int> p2 = { 0, 8, 15, 22, 29, 36};

  std::vector<Seed> ans;

  for(size_t i = 0; i < p1.size(); i++){
    ans.push_back(std::make_pair(p1[i],p2[i]));
  }

  std::vector<Seed> output = partitionPattern(P, np);
  matchSeed(output,ans);

  ans.clear();

  np=4;
  p1 = { "what_if_our", "_partition_", "was_as_long", "_as_a_text"};
  p2 = { 0, 11, 22, 33};
  for(size_t i = 0; i < p1.size(); i++){
    ans.push_back(std::make_pair(p1[i],p2[i]));
  }

  output = partitionPattern(P, np);
  matchSeed(output,ans);
  
}

TEST_CASE("partitionPattern Public Test 3", "[weight=5]") {
  std::string P = "ABCDEFGH";
  int np = 4;

  std::vector<std::string> p1 = { "AB" , "CD" , "EF" , "GH" };

  std::vector<int> p2 = { 0, 2, 4, 6 };

  std::vector<Seed> ans;

  for(size_t i = 0; i < p1.size(); i++){
    ans.push_back(std::make_pair(p1[i],p2[i]));
  }

  std::vector<Seed> output = partitionPattern(P, np);
  matchSeed(output,ans);

  ans.clear();

  P = "tcagagatagagatacagacacta";
  np=5;
  p1 = { "tcaga", "gatag", "agata", "cagac", "acta"};
  p2 = { 0, 5, 10, 15, 20};
  for(size_t i = 0; i < p1.size(); i++){
    ans.push_back(std::make_pair(p1[i],p2[i]));
  }

  output = partitionPattern(P, np);
  matchSeed(output,ans);
}

/*
* Public test cases for approximateSearch (Total 25 points / weight 25)
*/

TEST_CASE("approximate_search Public Test 1", "[weight=5]") {
  std::string fname = "../tests/data/pub1.txt";
  std::string P = "ABBA";
  int mm = 1;

  std::vector<int> ans = { 0, 5 };

  std::vector<int> output = approximate_search(fname, P, mm);
  matchVect(output,ans);

  P = "ABABAB";
  mm = 2;

  ans = {1, 3};

  output = approximate_search(fname, P, mm);
  matchVect(output,ans);
}

TEST_CASE("approximate_search Public Test 2", "[weight=5]") {
  std::string fname = "../tests/data/pub2.txt";
  std::string P = "zz";
  int mm = 1;

  std::vector<int> ans = { 1, 2, 3, 4, 5 };

  std::vector<int> output = approximate_search(fname, P, mm);
  matchVect(output,ans);

  P = "duck";
  mm = 1;

  ans = { 14, 32, 49};

  output = approximate_search(fname, P, mm);
  matchVect(output,ans);
}

TEST_CASE("approximate_search Public Test 3", "[weight=5]") {
  std::string fname = "../tests/data/pub3.txt";
  std::string P = "beep";
  int mm = 1;

  std::vector<int> ans = { 0, 5, 15, 20, 24, 29};

  std::vector<int> output = approximate_search(fname, P, mm);
  matchVect(output,ans);

  P = "meat";
  mm = 3;

  ans = { 0, 1, 5, 6, 10, 11, 15, 16, 20, 21, 24, 25, 29, 30, 33, 34};

  output = approximate_search(fname, P, mm);
  matchVect(output,ans);
}

TEST_CASE("approximate_search Public Test 4", "[weight=5]") {
  std::string fname = "../tests/data/pub3.txt";
  std::string P = "zebras";
  int mm = 1;

  std::vector<int> ans = { -1 };

  std::vector<int> output = approximate_search(fname, P, mm);
  matchVect(output,ans);

  fname = "../tests/data/pub1.txt";
  P = "zzzz";
  mm = 3;

  ans = { -1 };

  output = approximate_search(fname, P, mm);
  matchVect(output,ans);
}

TEST_CASE("approximate_search Public Test 5", "[weight=5]") {
  std::string fname = "../tests/data/five_sonnets.txt";
  std::string P = "bear";
  int mm = 1;

  std::vector<int> ans = { 81, 179, 764, 905, 1093, 1217, 1606, 2101, 2220, 2579, 3151, };

  std::vector<int> output = approximate_search(fname, P, mm);
  matchVect(output,ans);

  P = "besieg";
  mm = 2;

  ans = { 715 };

  output = approximate_search(fname, P, mm);
  matchVect(output,ans);
}