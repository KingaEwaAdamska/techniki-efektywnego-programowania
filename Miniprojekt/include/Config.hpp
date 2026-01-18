#pragma once

struct Config {
  static const int numberOfGroups = 12;
  static constexpr double capacityPenalty = 200000.0;
  static constexpr double lenPenalty = 200000.0;
  static const int startingPopulationSize = 3000;
  static const int removeInIteration = 15;
  static const int maxIterations = 500000;
  static int dimension;
  static int getGenLen() { return dimension - 1; }
};
