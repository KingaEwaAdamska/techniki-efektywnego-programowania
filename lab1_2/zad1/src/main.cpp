#include "table.hpp"

int main () {
  int *table;
  const int size = 12;

  if (!allocTableFill34(&table, size)){
    std::cout << "cannot allocate and fill table" << std::endl;
    return 1;
  }
  
  if (!showAllocatedTable(table, size)){
    std::cout << "cannot show table" << std::endl;
    return 1;
  }

  delete [] table;
  return 0;
}
