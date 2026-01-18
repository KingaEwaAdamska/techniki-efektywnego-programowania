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
    population.push_back(createRandomIndividual());
  }
}

Individual *Optimizer::createRandomIndividual() {
  Individual *individual = new Individual();
  std::uniform_int_distribution<int> dist(0, Config::numberOfGroups - 1);

  for (int i = 0; i <= Config::getGenLen(); i++) {
    individual->vals[i] = dist(randomGenerator);
  }
  return individual;
}

void Optimizer::showIndividual(Individual &individual) {
  for (int i = 0; i < Config::getGenLen(); i++) {
    std::cout << individual.vals[i] << " ";
  }
  std::cout << std::endl;
}

void Optimizer::runIteration() {
  removeWeakest(Config::removeInIteration);
  mutate();
  mutate();
  mutate();
  mutate();
}

void Optimizer::removeWeakest(int numToRm) {
  if (numToRm <= 0 || numToRm + 5 >= population.size())
    return;

  auto nth = population.begin() + numToRm;

  std::nth_element(population.begin(), nth, population.end(),
                   [this](Individual *a, Individual *b) {
                     return evaluator.evaluate(*a) > evaluator.evaluate(*b);
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

Individual *Optimizer::randomChangeInGen() {
  Individual *newInd = new Individual();
  std::uniform_int_distribution<int> distPop(0, population.size() - 1);
  int idx = distPop(randomGenerator);
  *newInd = *population[idx];

  std::uniform_int_distribution<int> distGene(0, Config::getGenLen() - 1);
  int geneIdx = distGene(randomGenerator);

  std::uniform_int_distribution<int> distVal(0, Config::numberOfGroups - 1);
  newInd->vals[geneIdx] = distVal(randomGenerator);

  return newInd;
}

Individual *Optimizer::mergeSmallGroups() {
  if (population.empty())
    return nullptr;

  std::uniform_int_distribution<int> distPop(0, population.size() - 1);
  int idx = distPop(randomGenerator);
  Individual *newInd = new Individual();
  *newInd = *population[idx];

  std::vector<int> counts(Config::numberOfGroups, 0);
  for (int i = 0; i < Config::getGenLen(); i++) {
    counts[newInd->vals[i]]++;
  }

  int min1 = -1, min2 = -1;
  for (int g = 0; g < Config::numberOfGroups; g++) {
    if (min1 == -1 || counts[g] < counts[min1]) {
      min2 = min1;
      min1 = g;
    } else if (min2 == -1 || counts[g] < counts[min2]) {
      min2 = g;
    }
  }

  for (int i = 0; i < Config::getGenLen(); i++) {
    if (newInd->vals[i] == min1)
      newInd->vals[i] = min2;
  }

  return newInd;
}

Individual *Optimizer::parentsMerge() {
  Individual *newInd = new Individual();
  if (population.size() < 2)
    return newInd;

  std::uniform_int_distribution<int> distPop(0, population.size() - 1);
  int idx1 = distPop(randomGenerator);
  int idx2 = distPop(randomGenerator);
  while (idx2 == idx1)
    idx2 = distPop(randomGenerator);

  Individual &parent1 = *population[idx1];
  Individual &parent2 = *population[idx2];

  std::uniform_int_distribution<int> distChoice(0, 1);
  for (int i = 0; i < Config::getGenLen(); i++) {
    newInd->vals[i] =
        distChoice(randomGenerator) ? parent1.vals[i] : parent2.vals[i];
  }

  return newInd;
}

void Optimizer::mutate() {
  std::uniform_int_distribution<int> distMut(0, 2);
  Individual *mutated = nullptr;

  int mutation = distMut(randomGenerator);
  if (mutation == 0) {
    mutated = randomChangeInGen();
  } else if (mutation == 1) {
    mutated = parentsMerge();
  } else {
    mutated = mergeSmallGroups();
  }

  population.push_back(mutated);
}

void Optimizer::printPopSize() {
  std::cout << "Size of population: " << population.size();
}
