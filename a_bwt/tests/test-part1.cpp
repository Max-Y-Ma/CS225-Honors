#include <catch2/catch_test_macros.hpp>

#include <string>
#include <iostream>
#include <vector>

#include "bwt.h"

/*
* Helper functions for basic tests
*/


void matchString(std::string output, std::string ans){

  REQUIRE(output.size() == ans.size());

  for(size_t i = 0; i < ans.size(); ++i){
    if(output[i]!=ans[i]){ 
      INFO("At index value: " + std::to_string(i) + " your string was incorrect.");
      REQUIRE(output[i] == ans[i]);
    }
  }
}


/*
* Public test cases for encode_bwt (Total 25 points / weight 25)
*/

TEST_CASE("Encode_BWT Public Test 1", "[weight=5]") {
  std::string T = "BABAAAB";
  std::string ans = "BBAABAA$";

  std::string bwt = encode_bwt(T);

  matchString(bwt,ans);
}

TEST_CASE("Encode_BWT Public Test 2", "[weight=5]") {
  std::string T = "ABCDEFG";
  std::string ans = "G$ABCDEF";

  std::string bwt = encode_bwt(T);

  matchString(bwt,ans);
}


TEST_CASE("Encode_BWT Public Test 3", "[weight=5]") {
  std::string T = "BBABBABABBA";
  std::string ans = "ABBBBBBABAA$";

  std::string bwt = encode_bwt(T);

  matchString(bwt,ans);
}

TEST_CASE("Encode_BWT Public Test 4 (English text)", "[weight=5]") {
  std::string T = "beep_beep_ima_sheep";
  std::string ans = "pppam$_hbbeees_ieee_";

  std::string bwt = encode_bwt(T);

  matchString(bwt,ans);
}

TEST_CASE("Encode_BWT Public Test 5 (Upper and Lower Case)", "[weight=5]") {
  std::string T = "Phnglui_mglwnafh_Cthulhu_Rlyeh_wgahnagl_fhtagn";
  std::string ans = "n_$_hulihnntgya_wanmafeaPfltuguggR_gwhhhChlh_ll";

  std::string bwt = encode_bwt(T);

  matchString(bwt,ans);
}

/*
* Public test cases for bwt_decode (Total 25 points / weight 25)
*/
TEST_CASE("decode_BWT Public Test 1", "[weight=5]") {
  std::string ans = "BABAAAB";
  std::string bwt = "BBAABAA$";

  std::string T = decode_bwt(bwt);

  matchString(T,ans);
}

TEST_CASE("decode_BWT Public Test 2", "[weight=5]") {
  std::string ans = "ABCDEFG";
  std::string bwt = "G$ABCDEF";

  std::string T = decode_bwt(bwt);

  matchString(T,ans);
}


TEST_CASE("decode_BWT Public Test 3", "[weight=5]") {
  std::string ans = "BBABBABABBA";
  std::string bwt = "ABBBBBBABAA$";

  std::string T = decode_bwt(bwt);

  matchString(T,ans);
}

TEST_CASE("decode_BWT Public Test 4 (English text)", "[weight=5]") {
  std::string ans = "beep_beep_ima_sheep";
  std::string bwt = "pppam$_hbbeees_ieee_";

  std::string T = decode_bwt(bwt);

  matchString(T,ans);
}

TEST_CASE("decode_BWT Public Test 5 (Upper and Lower Case)", "[weight=5]") {
  std::string ans = "Phnglui_mglwnafh_Cthulhu_Rlyeh_wgahnagl_fhtagn";
  std::string bwt = "n_$_hulihnntgya_wanmafeaPfltuguggR_gwhhhChlh_ll";

  std::string T = decode_bwt(bwt);

  matchString(T,ans);
}