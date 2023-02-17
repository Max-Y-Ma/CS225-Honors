/**
 * @file zstring.cpp
 * Support class for z-value and z-algorithm assignments
 *
 */

#include "zstring.h"
#include <cmath>
#include <iostream>

namespace cs225 {
  zstring::zstring(std::string & input) {
    i = 1;
    r = 0;
    l = 0;

    charComps = 0;

    s = input;
  }

  bool zstring::charMatch(int i, int j){
    charComps++;
    return s[i]==s[j];
  }

  int zstring::length(){
    return s.length();
  }

  int zstring::getCharComps(){
    return charComps;
  }

  void zstring::printCoords(){
    std::cout << "i, l, r: " << i << ", " << l << ", " << r << std::endl;
  }

  // NOTE: This is for debugging purposes only! 
  // DONT USE THIS TO DO CHARACTER COMPARISONS WHILE AVOIDING THE COUNTER
  // IT WILL NOT BE DEFINED IN THE ACTUAL AUTOGRADER (WILL CAUSE A CRASH)
  std::string zstring::getChar(int i){
    std::string str(1, s[i]);
    return str;
  }


}
