#pragma once

#include <cmath>
#include <string>
#include <vector>

struct Coordinate {
  double x;
  double y;

  Coordinate() : x(0.0), y(0.0) {}
  Coordinate(double x, double y) : x(x), y(y) {}

  double countDistance(Coordinate &other) {
    return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
  }

  static std::vector<std::vector<double>> *
  getDistances(std::vector<Coordinate> *coordinates);
}; // Coordinate

class ProblemData {
private:
  int dimension;
  int capacity;
  int *permutation; // kolejność miast po id
  int *demands;     // wymagania w kolejności id
  std::string type;
  std::vector<std::vector<double>> *distances;

public:
  void loadProblemFromFile(std::string filename);
  void print() const;
  int &getDimension() { return dimension; }
}; // ProblemData
