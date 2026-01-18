#include "ProblemData.hpp"
#include "Config.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

std::vector<std::vector<double>> *
Coordinate::getDistances(std::vector<Coordinate> *coordinates) {
  if (!coordinates)
    return nullptr;

  size_t n = coordinates->size();
  auto distances =
      new std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0));

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < i; ++j) {
      if (i == j) {
        (*distances)[i][j] = 0.0;
      } else {
        (*distances)[i][j] = (*distances)[j][i] =
            (*coordinates)[i].countDistance((*coordinates)[j]);
      }
    }
  }

  return distances;
}

void ProblemData::loadProblemFromFile(std::string filename) {
  std::string path = "../dane/" + filename;
  std::ifstream file(path);

  if (!file.is_open()) {
    std::cout << "Error: Cannot open file: " << path << std::endl;
    exit(1);
  }

  std::string line;

  while (getline(file, line)) {
    if (line.empty())
      continue;

    if (line.find("DIMENSION") != std::string::npos) {
      size_t colonPos = line.find(':');
      if (colonPos != std::string::npos) {
        int dimension = stoi(line.substr(colonPos + 1));
        Config::dimension = dimension;
      }
    } else if (line.find("CAPACITY") != std::string::npos) {
      size_t colonPos = line.find(':');
      if (colonPos != std::string::npos) {
        int capacity = stoi(line.substr(colonPos + 1));
        this->capacity = capacity;
      }
    } else if (line.find("EDGE_WEIGHT_SECTION") != std::string::npos) {
      distances = new std::vector<std::vector<double>>(
          Config::dimension, std::vector<double>(Config::dimension));

      for (int i = 1; i < Config::dimension; ++i) {
        for (int j = 0; j < i; ++j) {
          double distance;
          file >> distance;
          (*distances)[i][j] = distance;
          (*distances)[j][i] = distance;
        }
      }

    } else if (line.find("NODE_COORD_SECTION") != std::string::npos) {
      std::vector<Coordinate> *coordinates =
          new std::vector<Coordinate>(Config::dimension);

      for (int i = 0; i < Config::dimension; ++i) {
        int nodeId;
        double x, y;
        file >> nodeId >> x >> y;
        (*coordinates)[nodeId - 1] = Coordinate(x, y);
      }

      distances = Coordinate::getDistances(coordinates);
    } else if (line.find("DEMAND_SECTION") != std::string::npos) {
      demands = new int[Config::dimension];
      for (int i = 0; i < Config::dimension; ++i) {
        int nodeId, demand;
        file >> nodeId >> demand;
        std::cout << nodeId - 1 << " " << demand << std::endl;
        demands[nodeId - 1] = demand;
      }
    } else if (line.find("PERMUTATION") != std::string::npos) {
      size_t colonPos = line.find(':');
      permutation =
          new int[Config::getGenLen()]; // we dont take into account depot
      if (colonPos != std::string::npos) {
        std::string permData = line.substr(colonPos + 1);
        std::istringstream iss(permData);
        int customerId;
        int i = 0;
        while (iss >> customerId) {
          permutation[i++] = customerId;
        }
      }
    } else if (line.find("EOF") != std::string::npos) {
      break;
    }
  }
}

void ProblemData::print() const {
  std::cout << "=== Problem Data ===\n";

  std::cout << "Type: " << type << '\n';
  std::cout << "Dimension: " << Config::dimension << '\n';
  std::cout << "Capacity: " << capacity << "\n\n";

  std::cout << "Demands:\n";
  for (int i = 0; i < Config::dimension; ++i) {
    std::cout << "  Node " << i + 1 << ": " << demands[i] << '\n';
  }

  std::cout << "\nPermutation (order of nodes):\n";
  for (int i = 0; i < Config::getGenLen(); ++i) {
    std::cout << permutation[i] << ' ';
  }
  std::cout << "\n\n";

  std::cout << "Distance matrix:\n";
  std::cout << std::fixed << std::setprecision(2);
  for (int i = 0; i < Config::dimension; ++i) {
    for (int j = 0; j < Config::dimension; ++j) {
      std::cout << std::setw(8) << distances->at(i).at(j) << ' ';
    }
    std::cout << '\n';
  }
}

double ProblemData::getDistance(int x, int y) { return (*distances)[x][y]; }
