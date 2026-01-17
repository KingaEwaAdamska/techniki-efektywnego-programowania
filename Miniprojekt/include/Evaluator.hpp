#pragma once

#include "Individual.hpp"
#include "ProblemData.hpp"

class Evaluator {
private:
  ProblemData &problemData;

public:
  Evaluator(ProblemData &problemData);
  double evaluate(Individual &individual);
  int &getDimension() { return problemData.getDimension(); }
};
