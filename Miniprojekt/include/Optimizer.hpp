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
  std::mt19937 randomGenerator;

  Individual *createRandomIndividual();
  void removeWeakest(int numToRm);
  void mutate();

  // mutating styles
  Individual *randomChangeInGen();
  Individual *parentsMerge();
  Individual *mergeSmallGroups();

public:
  Optimizer(Evaluator &evaluator);
  ~Optimizer();

  void init();
  void runIteration();
  Individual &getCurrentBestSolution();
  void showIndividual(Individual &individual);
  void printPopSize();
};
