#include <format>
#include <cctype>
#include <fstream>
#include <iostream>
#include <ostream>
#include <regex>
#include <string>
#include <vector>
#include "day12.h"

using std::cout, std::endl;

enum SpringStatus {
  OK = '.',
  Damaged = '#',
  Unknown = '?'
};

bool isArrangementValid(const std::string& data, const std::regex& pattern) {
  return std::regex_match(data, pattern);
}

int validCombinationCountBraindead(std::string input, const std::regex& pattern) {
  std::vector<int> unknownPositions{};
  for (int i = 0; i < input.size(); i++) {
    if (input[i] == Unknown) {
      unknownPositions.push_back(i);
    }
  }

  cout << " = " << input << endl;

  int result = 0;
  int totalCombinations = 1 << unknownPositions.size();
  for (int i = 0; i < totalCombinations; ++i) {
    std::vector<bool> combination;

    for (int j = 0; j < unknownPositions.size(); ++j) {
      bool state = (i >> j) & 1;
      combination.emplace_back(state);
    }

    // replace ?'s
    for (const int pos: unknownPositions) {
      input[pos] = (combination[pos]) ? OK : Damaged ;
    }
    if (isArrangementValid(input, pattern)) {
      cout << " - " << input << endl;
      result += 1;
    }
  }

  return result;
}

void day12() {
  std::ifstream inputFile;
  inputFile.open("input_smol");
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

      if (currentNum.size() > 0) {
        damagedRanges.push_back(std::stoi(currentNum));
      }

      currentNum = "";
    }

    if (currentNum.size() > 0) {
      damagedRanges.push_back(std::stoi(currentNum));
    }

    for (const int& num: damagedRanges) {
      cout << num << ' ';
    }
    cout << endl;

    // prepare regex
    std::string regexStr = "^\\.*";
    for (int i = 0; i < damagedRanges.size(); i++){
      if (i > 0) {
        regexStr += "\\.+";
      }
      regexStr += std::format("#{{{}}}", std::to_string(damagedRanges[i]));

    }
    regexStr += "$";
    std::regex pattern(regexStr);

    int count = validCombinationCountBraindead(data, pattern);
    validCount += count;

    cout << lineNum << "/1000:\t" << count << '\t' << validCount << endl;
    ++lineNum;
  }
}
