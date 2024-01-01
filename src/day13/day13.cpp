//
// Created by jiric on 30.12.2023.
//

#include "day13.h"
#include <iostream>
#include <fstream>
#include <vector>

using std::cout;
using std::endl;

bool isValidPos(const std::vector<std::string>& values, int idxLeft) {
  size_t idxRight = idxLeft + 1;
  while (idxLeft >= 0 && idxRight < values.size()) {
    if (values[idxLeft] != values[idxRight]) {
      return false;
    }
    idxLeft--;
    idxRight++;
  }
  return true;
}

size_t mirroredPos(const std::vector<std::string>& values) {
  for (size_t i = 1; i < values.size(); i++) {
    if (values[i] == values[i-1]) {
      if (isValidPos(values, i-1)) {
        return i;
      }
    }
  }

  return 0;
}

void processStuff(size_t & result, std::vector<std::string>& rows, std::vector<std::string>& cols) {
  for (size_t i = 0; i < rows[0].size(); i++) {
    std::string col;
    for (const std::string& row: rows) {
      col.push_back(row[i]);
    }
    cols.push_back(col);
  }

  size_t rowPos = mirroredPos(rows);
  size_t colPos = mirroredPos(cols);

  result += colPos + 100 * rowPos;

  cols.clear();
  rows.clear();
}

void day13() {
  std::ifstream inputFile;
  inputFile.open("input/day13");
  std::string line;

  std::vector<std::string> rows;
  std::vector<std::string> cols;
  size_t result = 0;

  while (std::getline(inputFile, line)) {
    if (line.size() <= 1) {
      processStuff(result, rows, cols);
      continue;
    }

    std::string cleanedStr;
    for (const char& c: line) {
      if (c == '.' || c == '#') {
        cleanedStr.push_back(c);
      }
    }

    rows.push_back(cleanedStr);
  }

  inputFile.close();

  processStuff(result, rows, cols);
  cout << "Result is: " << result << endl;
}