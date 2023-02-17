/**
 * @file zstring.h
 *
 */

#pragma once

#include <iostream>
#include <sstream>
#include <string>

namespace cs225 {
  class zstring {
  public:
    int i; 
    int r; 
    int l; 

    zstring(std::string & input);

    // Returns the length of string s
    int length();

    void printCoords();

    // Your final code should only need checkChars
    bool charMatch(int i, int j);

    // This function can be helpful for debugging but should not be in your final submitted code.
    std::string getChar(int i);

    int getCharComps();

  private: 
    std::string s; 
    int charComps;
  };

}
