#include <iostream>
#include <string>

#define DEFAULT_NAME "table_name"

class Table{
private:
  std::string _name;
  int *_table;
  int _size;

public:
  static const int _defaultSize = 10;

  Table();
  Table(std::string name, int size);
  Table(const Table &otherTable);
  ~Table();

  void doubleClone(Table **tabClone0, Table **tabClone1);
  void fillWithNextNumbers();
  void showAllData();
  void setName(std::string newName);
  bool setNewSize(int newSize);
  Table* clone();
};

void modTable(Table *table, int newSize);
void modTable(Table table, int newSize);
