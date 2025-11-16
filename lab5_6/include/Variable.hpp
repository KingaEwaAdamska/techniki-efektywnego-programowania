struct Variable{
  std::string name;
  int occurrings;
  int value;
  Variable(std::string name){
    this->name = name;
    occurrings = 0;
  }
};
