#include <iostream>
#include <string>

#define DEFAULT_NAME "table_name"

class Table{
private:
  static const int _defaultSize = 10;

  std::string _name;
  int *_table;
  int _size;

public:
  Table();
  Table(std::string name, int size);
  Table(const Table &otherTable);
  ~Table();

  void setName(std::string newName);
  bool setNewSize(int newSize);
  Table* clone();
};

void modTable(Table *table, int newSize);
void modTable(Table table, int newSize);
