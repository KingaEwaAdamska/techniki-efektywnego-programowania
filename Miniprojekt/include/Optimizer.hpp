#pragma once

#include "Evaluator.hpp"
#include "Individual.hpp"
#include "ProblemData.hpp"
#include <random>

class Optimizer {
private:
  Evaluator &evaluator;
  ProblemData problemData;
  std::vector<Individual *> population;
  int dimension;
  std::mt19937 randomGenerator;

  Individual &createRandomIndividual();

public:
  Optimizer(Evaluator &evaluator);

  void init();
  void runIteration();
  Individual &getCurrentBestSolution();
  void showIndividual(Individual &individual);
};
