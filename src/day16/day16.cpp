//
// Created by jiric on 05.01.2024.
//

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include "day16.h"

class Field {
public:
    char value;
    bool isVisited;
    bool splitted;
    Field(char val){
      value = val;
      isVisited = false;
      splitted = false;
    };
};

using contraptionLayout = std::vector<std::vector<Field>>;

std::pair<int, int> RIGHT{0, 1};
std::pair<int, int> LEFT{0, -1};
std::pair<int, int> DOWN{1, 0};
std::pair<int, int> UP{-1, 0};

class Beam {
public:
    std::pair<int, int> pos;
    std::pair<int, int> direction;
    Beam(std::pair<int,int> p, std::pair<int,int> d) {
      pos = p;
      direction = d;
    }
    bool canContinue(const contraptionLayout& layout) const;
    Beam* evalPos(contraptionLayout& layout);
};

bool Beam::canContinue(const contraptionLayout &layout) const {
  if (pos.first >= 0 && pos.first < layout.size() &&
  pos.second >= 0 && pos.second < layout[pos.first].size()) {
    Field newField = layout[pos.first][pos.second];
    // check for endless loops
    // moving horizontally / vertically?
    if (direction.first == 0 && newField.value == '|') {
      return !newField.splitted;
    } else if (direction.second == 0 && newField.value == '-') {
      return !newField.splitted;
    }
    return true;
  }
  return false;
}

Beam* Beam::evalPos(contraptionLayout &layout) {
  /**+
   * Returns a beam if new beam is split
   */
  Field& field = layout[pos.first][pos.second];
  field.isVisited = true;

  // SPLITS
  if (field.value == '|') {
    // moving horizontaly
    if (direction.first == 0) {
      field.splitted = true;
      direction = UP;
      Beam* beam = new Beam(pos, DOWN);
      return beam;
    }
  }
  if (field.value == '-') {
    // moving vertically
    if (direction.second == 0) {
      field.splitted = true;
      direction = LEFT;
      Beam* beam = new Beam(pos, RIGHT);
      return beam;
    }
  }

  // REFLECTIONS
  if (field.value == '/') {
    if (direction == RIGHT) {
      direction = UP;
    } else if (direction == DOWN) {
      direction = LEFT;
    } else if (direction == LEFT) {
      direction = DOWN;
    } else if (direction == UP) {
      direction = RIGHT;
    }
  }
  if (field.value == '\\') {
    if (direction == RIGHT) {
      direction = DOWN;
    } else if (direction == DOWN) {
      direction = RIGHT;
    } else if (direction == LEFT) {
      direction = UP;
    } else if (direction == UP) {
      direction = LEFT;
    }
  }

  return nullptr;
}

void printLayout(const contraptionLayout& layout) {
  for (const auto& row: layout) {
    for (const Field& field: row) {
      if (field.isVisited) {
        std::cout << "#";
      } else {
        std::cout << ".";
      }
    }
    std::cout << std::endl;
  }
}

void energizeTiles(contraptionLayout& layout, std::pair<int, int> pos = {0, -1},
    std::pair<int, int> direction = RIGHT) {
  std::vector<Beam> beams;
  Beam initBeam(pos, direction);
  beams.push_back(initBeam);
  while (!beams.empty()) {
    std::vector<Beam> newBeams{};
    for (auto it = beams.begin(); it != beams.end();) {
      // move in direction
      it->pos.first += it->direction.first;
      it->pos.second += it->direction.second;
      if (it->canContinue(layout)) {
        Beam* b = it->evalPos(layout);
        it++;
        if (b != nullptr) {
          newBeams.push_back(*b);
        }
      } else {
        beams.erase(it);
      }
    }

    //add new beams
    beams.insert(beams.end(), newBeams.begin(), newBeams.end());
  }
}

int countEnergized(const contraptionLayout& layout) {
  int energizedTileCount = 0;
  for (const auto& row: layout) {
    for (const Field &field: row) {
      energizedTileCount += field.isVisited;
    }
  }

  return energizedTileCount;
}

void day16() {
  std::ifstream inputFile;
  inputFile.open("input/day16");
  std::string line;
  contraptionLayout layout;

  while (std::getline(inputFile, line)) {
    std::vector<Field> row;
    for (const char& c: line) {
      if (c == '/' || c == '\\' || c == '.' || c == '-' || c == '|') {
        Field field = *(new Field(c));
        row.push_back(field);
      }
    }
    layout.push_back(row);
  }
  inputFile.close();

  // copy layout
  contraptionLayout layoutClean = layout;

  energizeTiles(layout);

  int energizedTileCount = countEnergized(layout);

  std::cout << "Energized tiles: " << energizedTileCount << std::endl;

  energizedTileCount = 0;

  for (int row = 0; row < layout.size(); row++) {
    // first row / last row / regular row
    if (row == 0 ) {
      for (int col = 0; col < layout[row].size(); col++) {
        if (col == 0) {
          // corner from left
          contraptionLayout temp = layoutClean;
          energizeTiles(temp, {row, -1}, RIGHT);
          int newCount = countEnergized(temp);
          energizedTileCount = (newCount > energizedTileCount) ? newCount: energizedTileCount;


        } else if (col == layout[row].size()-1) {
          // corner from right
          contraptionLayout temp = layoutClean;
          energizeTiles(temp, {row, col+1}, LEFT);
          int newCount = countEnergized(temp);
          energizedTileCount = (newCount > energizedTileCount) ? newCount: energizedTileCount;
        } 
        contraptionLayout temp = layoutClean;
        energizeTiles(temp, {-1, col}, DOWN);
        int newCount = countEnergized(temp);
        energizedTileCount = (newCount > energizedTileCount) ? newCount: energizedTileCount;
      }
    } else if (row == layout.size()-1) {
      for (int col = 0; col < layout[row].size(); col++) {
        if (col == 0) {
          // corner from left
          contraptionLayout temp = layoutClean;
          energizeTiles(temp, {row, -1}, RIGHT);
          int newCount = countEnergized(temp);
          energizedTileCount = (newCount > energizedTileCount) ? newCount: energizedTileCount;

        } else if (col == layout[row].size()-1) {
          // corner from right
          contraptionLayout temp = layoutClean;
          energizeTiles(temp, {row, col+1}, LEFT);
          int newCount = countEnergized(temp);
          energizedTileCount = (newCount > energizedTileCount) ? newCount: energizedTileCount;
        } 
        contraptionLayout temp = layoutClean;
        energizeTiles(temp, {row+1, col}, UP);
        int newCount = countEnergized(temp);
        energizedTileCount = (newCount > energizedTileCount) ? newCount: energizedTileCount;
      }
    } else {
      int col = 0;
      contraptionLayout temp = layoutClean;
      energizeTiles(temp, {row, col-1}, RIGHT);
      int newCount = countEnergized(temp);
      energizedTileCount = (newCount > energizedTileCount) ? newCount: energizedTileCount;

      col = layout[row].size()-1;
      temp = layoutClean;
      energizeTiles(temp, {row, col+1}, RIGHT);
      newCount = countEnergized(temp);
      energizedTileCount = (newCount > energizedTileCount) ? newCount: energizedTileCount;
    }
  }

  std::cout << "Max energized tiles: " << energizedTileCount << std::endl;
}
