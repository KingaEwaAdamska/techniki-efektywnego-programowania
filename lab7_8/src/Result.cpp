#include "Result.hpp"
#include "Tree.hpp"


template <>
std::string Result<Tree*, Error>::errorsToString() {
  std::string result = "Tree: ";
  if (_value && *_value) {
    result += (*_value)->toString() + "\n";
  } else {
    result += "NULL\n";
  }
  int size = _errors.size();
  for (int i = 0; i < size; i++) {
    if (!result.empty()) {
      result += "\n";
    }
    result += _errors[i]->toString();
  }
  return result;
}

