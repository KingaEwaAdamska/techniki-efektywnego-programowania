#include "Table.hpp"

Table::Table(){
  _name = DEFAULT_NAME;
  _table = new int [_defaultSize];
  _size  = _defaultSize;

  std::cout << "bezp.: '" << _name << "'" << std::endl;
}

Table::Table(std::string name, int size){
  _name = name;
  if (size <= 0){
    size = _defaultSize;
  }
  _table = new int [size];
  _size = size;

  std::cout << "parametr: '" << _name << "'" << std::endl;
}

Table::Table(const Table &otherTable){
  _name = otherTable._name + "_copy";
  _table = new int [otherTable._size];
  _size = otherTable._size;
  for (int i = 0; i < otherTable._size; i++){
    _table[i] = otherTable._table[i];
  }

  std::cout << "kopiuj: '" << _name << "'" << std::endl;
}

Table::~Table(){
  delete [] _table;

  std::cout << "usuwam: '" << _name << "'" << std::endl;
}


void Table::setName(std::string newName){
  _name = newName;
}

bool Table::setNewSize(int newSize){
  if (newSize <= 0){
    return false;
  }else if (newSize <= _size){
    _size = newSize;
    return true;
  }
  
  int * newTable = new int[newSize];
  for (int i = 0; i < _size; i++){
    newTable[i] = _table[i];
  }
  _table = newTable;
  return true;
}

Table* Table::clone(){
  Table *newTable;
  newTable = new Table(*this);
  return newTable;
}

void modTable(Table *table, int newSize){
  table->setNewSize(newSize);
}

void modTable(Table table, int newSize){
  table.setNewSize(newSize);
}
