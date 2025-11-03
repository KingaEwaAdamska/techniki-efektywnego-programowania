#include "Table.hpp"

int main () {

  Table table;
  table.fillWithNextNumbers();

  std::cout << "table:" << std::endl;
  table.showAllData();
  
  Table *tableCopy1;
  Table *tableCopy2;
  table.doubleClone(&tableCopy1, &tableCopy2);

  std::cout << "tableCopy1:" << std::endl;
  tableCopy1->showAllData();
  std::cout << "tableCopy2:" << std::endl;
  tableCopy2->showAllData();
 
  delete tableCopy1;
  delete tableCopy2; 

  Table table2(table);

  Table *table3 = table.clone();
  Table *table4 = new Table("test", 5);


  delete table3;
  delete table4;
  return 0;
}
