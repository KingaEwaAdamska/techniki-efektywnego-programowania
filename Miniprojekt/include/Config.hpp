#pragma once

struct Config {
  static const int numberOfGroups = 10;
  static const int startingPopulationSize = 15;
  static const int chanceForMutation = 10;
  static const int maxIterations = 20;
  static int dimension;
  static int getGenLen() { return dimension - 1; }
};
