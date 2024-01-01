//
// Created by jiric on 30.12.2023.
//

#include "day13.h"
#include <iostream>
#include <fstream>
#include <vector>

using std::cout;
using std::endl;

int diffByOne(const std::string& a, const std::string& b) {
  if (a.size() != b.size()) {
    return -1;
  }

  int result = -1;
  for (int i = 0; i < a.size(); i++) {
    if (a[i] != b[i]) {
      // check if diff already found (result != -1)
      if (result > 0) {
        return -1;
      }
      result = i;
    }
  }

  return result;
}

bool isValidPosSmudge(const std::vector<std::string>& values, int idxLeft) {
  size_t idxRight = idxLeft + 1;
  bool smudgeUsed = false;
  while (idxLeft >= 0 && idxRight < values.size()) {
    if (values[idxLeft] != values[idxRight]) {
      int diff = diffByOne(values[idxLeft], values[idxRight]);
      if (diff >= 0 && !smudgeUsed) {
        smudgeUsed = true;
      } else {
        return false;
      }
    }
    idxLeft--;
    idxRight++;
  }

  return smudgeUsed;
}

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

size_t mirroredPos2(const std::vector<std::string>& values) {
  for (int i = 1; i < values.size(); i++) {
    if (values[i] == values[i - 1]) {
      if (isValidPosSmudge(values, i - 1)) {
        return i;
      }
    } else {
      // check diff
      int diff = diffByOne(values[i], values[i - 1]);
      if (diff >= 0) {
        std::string updatedLine = values[i];
        updatedLine[diff] = (updatedLine[diff] == '#') ? '.' : '#';
        std::vector<std::string> valuesCopy = values;
        valuesCopy[i] = updatedLine;

        if (isValidPos(valuesCopy, i - 1)) {
          return i;
        }
      }
    }
  }

  return 0;
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

void processStuff2(size_t & result, std::vector<std::string>& rows, std::vector<std::string>& cols) {
  for (size_t i = 0; i < rows[0].size(); i++) {
    std::string col;
    for (const std::string& row: rows) {
      col.push_back(row[i]);
    }
    cols.push_back(col);
  }

  size_t rowPos = mirroredPos2(rows);
  size_t colPos = mirroredPos2(cols);

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

  processStuff(result, rows, cols);
  cout << "Result for part 1 is: " << result << endl;

  inputFile.close();
  // part 2
  result = 0;
  inputFile.open("input/day13");
  while (std::getline(inputFile, line)) {
    if (line.size() <= 1) {
      processStuff2(result, rows, cols);
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

  processStuff2(result, rows, cols);
  cout << "Result for part 2 is: " << result << endl;
}