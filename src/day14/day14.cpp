//
// Created by jiric on 01.01.2024.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "day14.h"

std::pair<int, int> NORTH{-1, 0};

enum FieldType {
    RoundRock = 'O',
    SquareRock = '#',
    Empty = '.',
};

void printFields(const std::vector<std::vector<FieldType>>& fields) {
  for (const std::vector<FieldType>& row: fields) {
    for (const FieldType& field: row) {
      std::cout << char(field);
    }
    std::cout << std::endl;
  }
}

bool changePos(std::vector<std::vector<FieldType>>& fields,
        const std::pair<int, int>& src, const std::pair<int, int>& direction) {
  /**
   * Returns true if position was changed else returns false
   */
   if (fields[src.first][src.second] != RoundRock) {
     return false;
   }

  std::pair<int, int> newPos{src.first + direction.first, src.second + direction.second};
  if (newPos.first < 0 || newPos.first > (fields.size() - 1) ||
      newPos.second < 0 || newPos.second > (fields[newPos.first].size() -1)) {
    return false;
  }

  if (fields[newPos.first][newPos.second] != Empty) {
     return false;
  }


  fields[newPos.first][newPos.second] = RoundRock;
  fields[src.first][src.second] = Empty;
  return true;
}

void moveLever(std::vector<std::vector<FieldType>>& fields, std::pair<int,int> direction) {
  bool somethingChanged = true;
  std::pair<int, int> fieldDimensions{fields.size(), fields[0].size()};
  while (somethingChanged) {
    somethingChanged = false;
    for (int rowNum = 0; rowNum < fieldDimensions.first; rowNum++) {
      for (int colNum = 0; colNum < fieldDimensions.second; colNum++) {
        // check if round
        if (fields[rowNum][colNum] == RoundRock) {
          somethingChanged += changePos(fields, {rowNum, colNum}, direction);
        }
      }
    }
  }
}

int calculateLoad(const std::vector<std::vector<FieldType>>& fields) {
  int totalLoad = 0;

  int singleRockLoad = fields.size();
  for (const std::vector<FieldType> row: fields) {
    for (const FieldType& field: row) {
      if (field == RoundRock) {
        totalLoad += singleRockLoad;
      }
    }
    singleRockLoad--;
  }

  return  totalLoad;
}

void day14() {
  std::ifstream inputFile;
  inputFile.open("input/day14");
  std::vector<std::vector<FieldType>> fields;
  std::string line;

  int row = 0;
  while(std::getline(inputFile, line)) {
    line = (line.back() == 13) ? line.substr(0, line.size()-1) : line;
    fields.emplace_back();
    for (const char& c : line) {
      fields[row].push_back(FieldType(c));
    }
    row++;
  }

  // move all north
  moveLever(fields, NORTH);
  std::cout << std::endl;

  int totalLoad = calculateLoad(fields);
  std::cout << "Total load after 1 cycle: " << totalLoad << std::endl;
}
