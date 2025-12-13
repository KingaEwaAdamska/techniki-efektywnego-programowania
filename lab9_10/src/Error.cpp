#include "Error.hpp"

Error::Error(std::string message) {
  errorMessage = message;
}

std::string Error::toString(){
  return errorMessage;
}

Error::Error(const Error& other){
  errorMessage = other.errorMessage;
}
