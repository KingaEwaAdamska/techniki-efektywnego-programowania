#include "Optimizer.hpp"
#include "Config.cpp"
#include <iostream>

Optimizer::Optimizer(Evaluator &evaluator)
    : evaluator(evaluator), randomGenerator(std::random_device{}()) {
  dimension = evaluator.getDimension();
}

void Optimizer::init() {
  for (int i = 0; i < config::startingPopulationSize; i++) {
    population.push_back(&createRandomIndividual());
  }
}

Individual &Optimizer::createRandomIndividual() {
  Individual *individual = new Individual(dimension);
  std::uniform_int_distribution<int> dist(0, config::numberOfGroups - 1);

  for (int i = 0; i < dimension - 1; i++) {
    individual->vals[i] = dist(randomGenerator);
  }
  showIndividual(*individual);
  return *individual;
}

void Optimizer::showIndividual(Individual &individual) {

  for (int i = 0; i < dimension - 1; i++) {
    std::cout << individual.vals[i] << " ";
  }
  std::cout << std::endl;
}
