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
  int capacity;
  int *permutation; // kolejność miast po id
  int *demands;     // wymagania w kolejności id
  double maxDistance = 0.0;
  std::string type;
  std::vector<std::vector<double>> *distances;

public:
  void loadProblemFromFile(std::string filename);
  void print() const;
  int getPerm(int id) { return permutation[id]; }
  int getDemand(int id) { return demands[id]; }
  int getCapacity() { return capacity; }
  double getDistance(int x, int y);
  double getMaxDistance() { return maxDistance; }
}; // ProblemData
