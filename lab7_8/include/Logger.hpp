#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "Tree.hpp"

class Logger {
  public:
    Logger(const std::string& filename);
    ~Logger();

    template <typename T, typename E>
    void logResult(Result<T, E>& result) {
      _logFile << _getCurrentTime() << " " << std::endl;
    }

  private:
    std::ofstream _logFile;
    std::string _getCurrentTime();
};

