#pragma once

#include "Individual.hpp"
#include "ProblemData.hpp"
#include <vector>

class Evaluator {
private:
  ProblemData &problemData;

  std::vector<std::vector<int>> *buildRoutes(Individual &individual);
  double evalRouteLen(std::vector<int> &route);
  double evalCapacityPenalty(const std::vector<int> &route);

public:
  Evaluator(ProblemData &problemData);
  double evaluate(Individual &individual);
};
