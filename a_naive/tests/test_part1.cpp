#include <catch2/catch_test_macros.hpp>
#include "naive.cpp"

/*
* Test cases for Naive search (Total 30 points / weight 30)
*/
TEST_CASE("Naive search finds only pattern match.", "[weight=5]") {
  std::string P = "AAA";
  std::string T = "BAAAT";
  REQUIRE( naive_search(P,T) == 1 );
}

TEST_CASE("Naive search finds first pattern match.", "[weight=5]") {
  std::string P = "pattern";
  std::string T = "this is a pattern that has a repeat pattern";
  REQUIRE( naive_search(P,T) == 10 );

  P = "Matters";
  T = "It matters that the third matters Matters. It also Matters that this sentence also matters";
  REQUIRE( naive_search(P,T) == 34);
}

TEST_CASE("Naive search handles no pattern match.", "[weight=5]") {
  std::string P = "zebras";
  std::string T = "There is no match in this text.";
  REQUIRE( naive_search(P,T) == -1 );
}

TEST_CASE("Naive search does not crash when pattern larger than text.", "[weight=5]") {
  std::string P = "Oops all patterns";
  std::string T = "Oops";
  REQUIRE( naive_search(P,T) == -1 );
}

TEST_CASE("Naive search handles case where pattern is equal to text.", "[weight=5]") {
  std::string P = "Oops";
  std::string T = "Oops";
  REQUIRE( naive_search(P,T) == 0 );
}

TEST_CASE("Naive search is case sensitive.", "[weight=5]") {
  std::string P = "Matters";
  std::string T = "It matters that the third matters Matters. Here's some more padding to make it harder to cheat.";
  REQUIRE( naive_search(P,T) == 34 );
}

/*
* Test cases for longest common prefix search (Total 30 points / weight 30)
*/
TEST_CASE("LCP search finds the longest possible prefix match.", "[weight=10]") {
  std::string P = "beep fish";
  std::string T = "beep fish pizza is not a good pizza. we now repeat beep fish beep fish beep";
  REQUIRE( longest_common_prefix(P,T) == "beep fish" );

  P = "aaab";
  T = "aaaaaa";
  REQUIRE( longest_common_prefix(P,T) == "aaa" );

  P = "aaaa";
  T = "aaaa";
  REQUIRE( longest_common_prefix(P,T) == "aaaa" );

  P = "too much clutter";
  T = "too much cleaning to do";
  REQUIRE( longest_common_prefix(P,T) == "too much cl" );
}

TEST_CASE("LCP search handles no pattern match.", "[weight=5]") {
  std::string P = "zebras";
  std::string T = "There is no prefix match in this text.";
  REQUIRE( longest_common_prefix(P,T) == "");

  P = "bbb";
  T = "aaaaaa";
  REQUIRE( longest_common_prefix(P,T) == "" );

}

TEST_CASE("LCP search ignores matches that arent prefixes.", "[weight=10]") {
  std::string P = "suffix";
  std::string T = "This text matches a suffix";
  REQUIRE( longest_common_prefix(P,T) == "" );

  P = "match";
  T = "there is a match but its not a prefix match";
  REQUIRE( longest_common_prefix(P,T) == "" );

  P = "tiny match";
  T = "there is a tiny match but its not a prefix match";
  REQUIRE( longest_common_prefix(P,T) == "t" );
}

TEST_CASE("LCP search is case sensitive.", "[weight=5]") {
  std::string P = "Prefix";
  std::string T = "prefix is different from Prefix";
  REQUIRE( longest_common_prefix(P,T) == "" );

  P = "prefix isnt";
  T = "prefix is different from Prefix";
  REQUIRE( longest_common_prefix(P,T) == "prefix is" );

  P = "Matters";
  T = "Ma it matters that the third matters Matters. It also Matters that this sentence also matters";
  REQUIRE( longest_common_prefix(P,T) == "Ma" );
}

/*
* Test cases for LCS search (Total 25 points / weight 40)
*/
TEST_CASE("LCS search finds longest possible suffix.", "[weight=10]") {
  std::string P = "ends";
  std::string T = "The story ends the way it ends";
  REQUIRE( longest_common_suffix(P,T) == "ends" );

  P = "aaaa";
  T = "aaaaaa";
  REQUIRE( longest_common_suffix(P,T) == "aaaa" );

  P = "baaa";
  T = "aaaa";
  REQUIRE( longest_common_suffix(P,T) == "aaa" );

  P = "tcgatacagatga";
  T = "cgtagcatagatacatagatga";
  REQUIRE( longest_common_suffix(P,T) == "agatga" );
}

TEST_CASE("LCS search handles no pattern match.", "[weight=10]") {
  std::string P = "zebras";
  std::string T = "There is no match in this text.";
  REQUIRE( longest_common_suffix(P,T) == "" );

  P = "qqq";
  T = "bbbb";
  REQUIRE( longest_common_suffix(P,T) == "" );

  P = "match";
  T = "there is almost a match but punctuation stops the match.";
  REQUIRE( longest_common_suffix(P,T) == "" );
}

TEST_CASE("LCS search ignores matches that arent suffixes.", "[weight=10]") {
  std::string P = "prefix";
  std::string T = "prefix prefix not a suffix";
  REQUIRE( longest_common_suffix(P,T) == "fix" );

  P = "tiny match";
  T = "there is a tiny match but its not a full length match";
  REQUIRE( longest_common_suffix(P,T) == " match" );
}

TEST_CASE("LCS search is case sensitive.", "[weight=10]") {
  std::string P = "Prefix";
  std::string T = "prefix is different from Prefix";
  REQUIRE( longest_common_suffix(P,T) == "Prefix" );
  P = "prefix";
  REQUIRE( longest_common_suffix(P,T) == "refix" );

  P = "Matters";
  T = "It matters that the third matters Matters. It also Matters that this sentence also matters";
  REQUIRE( longest_common_suffix(P,T) == "atters" );
}