struct Variable{
  Variable(const Variable& other) 
    : name(other.name), occurrings(other.occurrings), value(other.value) {
  }
  std::string name;
  int occurrings;
  int value;
  Variable(std::string name){
    this->name = name;
    occurrings = 1;
  }
};
