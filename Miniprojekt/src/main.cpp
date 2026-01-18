#include "Config.hpp"
#include "Evaluator.hpp"
#include "Individual.hpp"
#include "Optimizer.hpp"

int Config::dimension = 0;

int main() {
  ProblemData problemData;
  problemData.loadProblemFromFile("1.lcvrp");
  problemData.print();

  Evaluator evaluator(problemData);
  Optimizer optimizer(evaluator);

  optimizer.init();
  for (int i = 0; i < Config::maxIterations; i++) {
    optimizer.runIteration();
  }

  optimizer.printPopSize();
  Individual &ind = optimizer.getCurrentBestSolution();

  ind.print();
}
