#include "StringHandler.hpp"

std::vector<std::string>* StringHandler::divideLineIntoTokensAndCommand(const std::string &line, std::string &command){
  std::vector<std::string> *tokens = new std::vector<std::string>;

  std::stringstream ss(line);
  std::string token;

  if (ss >> token) {
    command = token;
  }

  while (ss >> token) {
    tokens->push_back(token);
  }

  return tokens;
}

bool StringHandler::isNumber(const std::string& str) {
  if (str.empty()) return false;
    
  bool hasDecimal = false;
  bool hasDigit = false;
    
  for (int i = 0; i < str.length(); i++) {
      if (i == 0 && str[i] == '-' && str.length() > 1) {
        continue;
      }
      if (str[i] == '.') {
          if (hasDecimal) return false;
          hasDecimal = true;
        } else if (!isdigit(str[i])) {
          return false;
        } else {
          hasDigit = true;
        }
    }
    return hasDigit;
}

float StringHandler::stringToFloat(const std::string& str) { 
  return static_cast<float>(atof(str.c_str()));
}
