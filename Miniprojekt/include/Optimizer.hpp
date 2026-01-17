#pragma once

#include "Evaluator.hpp"
#include "ProblemData.hpp"
#include "Solution.hpp"

class Optimizer {
private:
  Evaluator &evaluator;
  ProblemData problemData;

public:
  Optimizer(Evaluator &evaluator);

  void runIteration();
  Solution *getCurrentBestSolution();
};
