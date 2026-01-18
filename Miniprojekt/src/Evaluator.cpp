#include "Evaluator.hpp"
#include "Config.hpp"
#include <limits>
#include <vector>

Evaluator::Evaluator(ProblemData &problemData) : problemData(problemData) {}

double Evaluator::evaluate(Individual &individual) {
  if (individual.eval_val != std::numeric_limits<double>::max())
    return individual.eval_val;

  double evaluated_val = 0.0;

  std::vector<std::vector<int>> *routes = buildRoutes(individual);

  for (int i = 0; i < Config::numberOfGroups; i++) {
    double len = evalRouteLen((*routes)[i]);
    if (problemData.getMaxDistance() != 0.0 &&
        len > problemData.getMaxDistance()) {
      evaluated_val += Config::lenPenalty;
    }
    evaluated_val += len;
    evaluated_val += evalCapacityPenalty((*routes)[i]);
  }

  delete routes;

  individual.eval_val = evaluated_val;
  return evaluated_val;
}

std::vector<std::vector<int>> *Evaluator::buildRoutes(Individual &individual) {

  auto *routes = new std::vector<std::vector<int>>(Config::numberOfGroups);

  for (int i = 0; i < Config::getGenLen(); i++) {

    int city = problemData.getPerm(i);

    if (city < 0) {
      exit(1);
    }

    int group = individual.vals[city - 1];

    if (group < 0 || group >= Config::numberOfGroups) {
      exit(1);
    }

    (*routes)[group].push_back(city);
  }

  return routes;
}

double Evaluator::evalRouteLen(std::vector<int> &route) {
  if (route.empty()) {
    return 0.0;
  }

  double len = 0.0;
  for (int i = 1; i < route.size(); i++) {
    len += problemData.getDistance(route[i - 1] - 1, route[i] - 1);
  }

  len += problemData.getDistance(route[0] - 1, 0);
  len += problemData.getDistance(route.back() - 1, 0);

  return len;
}

double Evaluator::evalCapacityPenalty(const std::vector<int> &route) {
  int load = 0;

  for (int city : route) {
    load += problemData.getDemand(city - 1);
  }

  int excess = load - problemData.getCapacity();
  if (excess > 0) {
    return Config::capacityPenalty;
  }

  return 0.0;
}
