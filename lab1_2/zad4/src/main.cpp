#include "Table.hpp"

int main () {
  Table table;
  Table table2(table);

  Table *table3 = table.clone();
  Table *table4 = new Table("test", 5);

  delete table3;
  delete table4;
  return 0;
}
