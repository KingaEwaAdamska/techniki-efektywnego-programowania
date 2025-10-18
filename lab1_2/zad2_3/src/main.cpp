#include "table2Dim.hpp"
#include <iostream>

int main () {
  int **table;
  const int sizeX = 5;
  const int sizeY = 3;

  if (!allocTable2Dim(&table, sizeX, sizeX)){
    std::cout << "cannot allocate and fill table" << std::endl;
    return 1;
  }
  
  if (!deallocTable2Dim(&table, sizeX)){
    std::cout << "cannot deallocate table" << std::endl;
    return 1;
  }
  return 0;
}
