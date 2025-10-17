#include "table2Dim.hpp"

bool allocTable2Dim(int ***table, int sizeX, int sizeY){
  if (sizeX <= 0 || sizeY <= 0) {
    return false;
  }
  *table = new int*[sizeX];
  for (int i = 0; i < sizeX; i++){
    (*table)[i] = new int [sizeY];
  }
  return true;
}

bool deallocTable2Dim(int ***table, int sizeX){
  if (sizeX <= 0){
    return false;
  }
  for (int i = 0; i < sizeX; i++){
    delete [] (*table)[i];
  }
  delete [] *table;
  return true;
}
