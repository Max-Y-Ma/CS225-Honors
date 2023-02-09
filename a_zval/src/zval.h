/**
 * @file zval.h
 * Declarations of z-algorithm pattern matching functions.
 */

#pragma once

#include <string>
#include <vector>

std::pair<int, int> lr_scan(std::string P, std::string T);
int create_zarray(std::string S, int* Z);
std::vector<int> zval_search(std::string P, std::string T);