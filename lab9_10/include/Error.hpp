#pragma once
#include <string>

class Error{
  public:
    Error(std::string message);
    Error(const Error& other);
    std::string toString();
  private: 
    std::string errorMessage;
};
