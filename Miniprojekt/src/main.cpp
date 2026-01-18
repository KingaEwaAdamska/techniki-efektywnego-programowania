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
  for (int i = 0; i < 2; i++) {
    optimizer.runIteration();
  }

  Individual &ind = optimizer.getCurrentBestSolution();
  std::cout << "docieram tu" << std::endl;
  ind.print();
}
