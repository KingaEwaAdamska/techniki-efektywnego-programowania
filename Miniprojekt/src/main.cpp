#include "Evaluator.hpp"
#include "Optimizer.hpp"

int main() {
  ProblemData problemData;
  problemData.loadProblemFromFile("1.lcvrp");
  problemData.print();

  Evaluator evaluator(problemData);
  Optimizer optimizer(evaluator);

  optimizer.init();
}
