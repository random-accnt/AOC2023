#include <iostream>
#include "day12/day12.h"
#include "day13/day13.h"
#include "day14/day14.h"
#include "day15/day15.h"
#include "day16/day16.h"

int main (int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <day_number>\n";
    return 1;
  }

  int dayNum;

  try {
    dayNum = std::stoi(argv[1]);
  } catch (const std::invalid_argument& e) {
    std::cout << "Invalid argument: " << e.what() << std::endl;
    return 1;
  } catch (const std::out_of_range& e) {
    std::cout << "Argument out of range: " << e.what() << std::endl;
    return 1;
  }

  switch (dayNum) {
    case 12:
      day12();
      break;
    case 13:
      day13();
      break;
    case 14:
      day14();
      break;
    case 15:
      day15();
      break;
    case 16:
      day16();
      break;
    default:
      std::cout << "Solution for day " << dayNum << " not implemented.\n";
  }

  return 0;
}
