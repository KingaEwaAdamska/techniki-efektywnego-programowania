#include "Optimizer.hpp"
#include "Config.hpp"
#include <algorithm>
#include <iostream>

Optimizer::Optimizer(Evaluator &evaluator)
    : evaluator(evaluator), randomGenerator(std::random_device{}()) {}

Optimizer::~Optimizer() {
  for (int i = 0; i < population.size(); i++) {
    delete population[i];
  }
}

void Optimizer::init() {
  for (int i = 0; i < Config::startingPopulationSize; i++) {
    population.push_back(&createRandomIndividual());
  }
}

Individual &Optimizer::createRandomIndividual() {
  Individual *individual = new Individual();
  std::uniform_int_distribution<int> dist(0, Config::numberOfGroups - 1);

  for (int i = 0; i <= Config::getGenLen(); i++) {
    individual->vals[i] = dist(randomGenerator);
  }
  showIndividual(*individual);
  return *individual;
}

void Optimizer::showIndividual(Individual &individual) {
  for (int i = 0; i < Config::getGenLen(); i++) {
    std::cout << individual.vals[i] << " ";
  }
  std::cout << std::endl;
}

void Optimizer::runIteration() { removeWeakest(3); }

void Optimizer::removeWeakest(int numToRm) {
  if (numToRm <= 0 || numToRm >= population.size())
    return;

  auto nth = population.begin() + numToRm;

  std::nth_element(population.begin(), nth, population.end(),
                   [this](Individual *a, Individual *b) {
                     return evaluator.evaluate(*a) < evaluator.evaluate(*b);
                   });

  for (auto it = population.begin(); it != nth; ++it) {
    delete *it;
  }

  population.erase(population.begin(), nth);
}

Individual &Optimizer::getCurrentBestSolution() {
  if (population.empty()) {
    throw std::runtime_error("Population is empty");
  }

  auto bestIt =
      std::min_element(population.begin(), population.end(),
                       [this](Individual *a, Individual *b) {
                         return evaluator.evaluate(*a) < evaluator.evaluate(*b);
                       });

  return **bestIt;
}
