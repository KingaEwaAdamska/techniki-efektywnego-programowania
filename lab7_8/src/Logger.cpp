#include "Logger.hpp"

Logger::Logger(const std::string& filename) {
  _logFile.open(filename.c_str(), std::ios::out | std::ios::app);

  if (!_logFile.is_open()) {
    std::cerr << "Error: Cannot open file: " << filename << std::endl;
  }
}

Logger::~Logger() {
  if (_logFile.is_open()) {
    _logFile.close();
  }
}

std::string Logger::_getCurrentTime() {
  time_t rawtime;
  struct tm * timeinfo;
  char buffer[80];

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer, sizeof(buffer), "[%Y-%m-%d %H:%M:%S]", timeinfo);

  return std::string(buffer);
}

