#pragma once
#include "Config.hpp"
#include <iostream>
#include <limits>

struct Individual {
  int *vals;
  double eval_val = std::numeric_limits<double>::max();

  Individual() : vals(new int[Config::getGenLen()]) {}

  void print() const {
    std::cout << "[ ";
    for (int i = 0; i < Config::getGenLen(); i++) {
      std::cout << vals[i] << " ";
    }
    std::cout << "]  eval = " << eval_val << std::endl;
  }

  ~Individual() { delete[] vals; }
};
