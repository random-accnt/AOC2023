#include <cctype>
#include <fstream>
#include <iostream>
#include <ostream>
#include <regex>
#include <string>
#include <vector>
#include "day12.h"

using std::cout;
using std::endl;

enum SpringStatus {
  OK = '.',
  Damaged = '#',
  Unknown = '?'
};

void printBinary(int num) {
    int bits = sizeof(num) * 8;
    unsigned int mask = 1 << (bits - 1 );
    while (mask > 0) {
        if (num & mask)
            printf("1");
        else
            printf("0");

        mask >>= 1;
    }
    printf("\n");
}

bool isArrangementValid(const std::string& data, const std::regex& pattern) {
  return std::regex_match(data, pattern);
}

int validCombinationCountBraindead(std::string input, const std::regex& pattern) {
  std::vector<int> unknownPositions{};
  for (int i = 0; i < static_cast<int>(input.size()); i++) {
    if (input[i] == Unknown) {
      unknownPositions.push_back(i);
    }
  }

  int result = 0;
  int totalCombinations = 1 << unknownPositions.size();
  for (int i = 0; i < totalCombinations; ++i) {
    std::vector<bool> combination;

    unsigned int mask = 1 << (unknownPositions.size() - 1);
    while (mask > 0) {
      bool state = i & mask;
      combination.push_back(state);
      mask >>= 1;
    }

    // replace ?'s
    auto combinationValue = combination.begin();
    for (const int& pos: unknownPositions) {
      input[pos] = (*combinationValue) ? OK : Damaged ;
      combinationValue++;
    }
    if (isArrangementValid(input, pattern)) {
      result += 1;
    }
  }

  return result;
}

void day12() {
  std::ifstream inputFile;
  inputFile.open("input/day12");
  std::string line;
  int validCount = 0;
  int lineNum = 1;

  while (std::getline(inputFile, line)) {
    std::string data = line.substr(0, line.find(' '));
    std::string rangesStr = line.substr(line.find(' ')+1);
    std::vector<int> damagedRanges{};

    std::string currentNum = "";
    for (const char& c: rangesStr) {
      if (std::isdigit(c)) {
        currentNum.push_back(c);
        continue;
      }

      if (!currentNum.empty()) {
        damagedRanges.push_back(std::stoi(currentNum));
      }

      currentNum = "";
    }

    if (!currentNum.empty()) {
      damagedRanges.push_back(std::stoi(currentNum));
    }

    // prepare regex
    std::string regexStr = "^\\.*";
    for (size_t i = 0; i < damagedRanges.size(); i++){
      if (i > 0) {
        regexStr += "\\.+";
      }
      regexStr += "#{";
      regexStr += std::to_string(damagedRanges[i]);
      regexStr += "}";

    }
    regexStr += "\\.*$";
    std::regex pattern(regexStr);

    int count = validCombinationCountBraindead(data, pattern);
    validCount += count;

    cout << lineNum << "/1000:\t" << count << '\t' << validCount << endl;
    ++lineNum;
  }

  cout << "Valid combinations: " << validCount << endl;
}
