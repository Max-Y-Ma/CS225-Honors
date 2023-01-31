/**
 * @file naive.h
 * Declarations of naive pattern matching functions.
 */

#pragma once

#include <string>

int naive_search(std::string P, std::string T);
std::string longest_common_prefix(std::string P, std::string T);
std::string longest_common_suffix(std::string P, std::string T);