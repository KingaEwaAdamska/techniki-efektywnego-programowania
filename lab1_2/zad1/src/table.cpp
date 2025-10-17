#include "table.hpp"

bool allocTableFill34(int **table, int size){
  if (size <= 0) {
    return false;
  }
  *table = new int[size];
  for (int i = 0; i < size; i++){
    (*table)[i] = val34;
  }
  return true;
}

bool showAllocatedTable(int *table, int size){
  if (size <= 0) {
    return false;
  }
  for (int i = 0; i < size; i++) {
    std::cout << table[i] << " ";
  }
  std::cout << std::endl;
  return true;
}
