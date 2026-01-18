#pragma once
#include "Config.hpp"
#include <iostream>
#include <limits>

struct Individual {
  int *vals;
  double eval_val = std::numeric_limits<double>::max();

  Individual() : vals(new int[Config::getGenLen()]) {}

  Individual(const Individual &other)
      : vals(new int[Config::getGenLen()]), eval_val(other.eval_val) {
    for (int i = 0; i < Config::getGenLen(); i++)
      vals[i] = other.vals[i];
  }

  ~Individual() { delete[] vals; }

  Individual &operator=(const Individual &other) {
    if (this != &other) {
      eval_val = other.eval_val;
      for (int i = 0; i < Config::getGenLen(); i++)
        vals[i] = other.vals[i];
    }
    return *this;
  }

  void print() const {
    std::cout << "[ ";
    for (int i = 0; i < Config::getGenLen(); i++) {
      std::cout << vals[i] << " ";
    }
    std::cout << "]  eval = " << eval_val << std::endl;
  }
};
