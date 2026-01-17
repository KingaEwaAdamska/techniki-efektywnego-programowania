#pragma once

#include "ProblemData.hpp"
#include "Solution.hpp"

class Evaluator {
private:
  ProblemData &problemData;

public:
  Evaluator(ProblemData &problemData);
  double evaluate(Solution *solution);
};
