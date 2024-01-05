//
// Created by jiric on 03.01.2024.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include "day15.h"

using LensType = std::pair<std::string, int>;
using BoxLensType = std::map<int, std::vector<LensType>>;

void addLens(std::vector<LensType>& boxLens, LensType& lens) {
  auto currentLens = std::find_if(boxLens.begin(), boxLens.end(), [&lens](const LensType& l) {
    return l.first == lens.first;
  });

  if (currentLens == boxLens.end()) {
    boxLens.push_back(lens);
  } else {
    currentLens->second = lens.second;
  }
}

void removeLens(std::vector<LensType>& boxLens, std::string name) {
  auto currentLens = std::find_if(boxLens.begin(), boxLens.end(), [&name](const LensType &l) {
      return l.first == name;
  });

  if (currentLens != boxLens.end()) {
    boxLens.erase(currentLens);
  }
}

int hashStr(const std::string& str) {
  int hash = 0;
  for (const char& c: str) {
    hash += c;
    hash *= 17;
    hash %= 256;
  }

  return hash;
}

void day15() {
  std::ifstream inputFile;
  inputFile.open("input/day15");
  std::string line;

  // read into line
  std::getline(inputFile, line);
  inputFile.close();

  std::stringstream ss(line);
  std::string token;
  int hashSum;
  BoxLensType boxesOfLens;
  while (std::getline(ss, token, ',')) {
    // part 1
    int hashFull = hashStr(token);
    hashSum += hashFull;

    // part 2
    std::string label;
    int breakPos = 1;
    bool isAdd;
    for (const char& c: token) {
      if (c == '-' || c == '=') {
        isAdd = c == '=';
        break;
      }
      breakPos++;
      label.push_back(c);
    }
    int hashLabel = hashStr(label);

    int num = 0;
    if (breakPos < token.size()) {
      num = std::stoi(token.substr(breakPos));
    }

    std::vector<LensType>& singleBox = boxesOfLens[hashLabel];
    if (isAdd) {
      std::pair<std::string, int> x = *(new std::pair<std::string, int>(label, num));
      addLens(singleBox, x);
    } else {
      removeLens(singleBox, label);
    }

  }

  int result2 = 0;
  for (const auto& hashLens: boxesOfLens) {
    int slot = 1;

    for (const LensType& lensNum: hashLens.second) {
      result2 += (1 + hashLens.first) * slot * lensNum.second;
      slot++;
    }
  }

  std::cout << "Sum of hashes is: " << hashSum << std::endl;
  std::cout << "Focusing power is: " << result2 << std::endl;
}
