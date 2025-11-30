#ifndef INTERFACE_HPP
#define INTERFACE_HPP
#define LOG_FILE "log.txt"

#include "Tree.hpp"
#include "Logger.hpp"
#include <string>
#include <vector>

class CmdInterface {
  private:
    Tree* tree;
    Logger* logger;
    std::string command;
    std::vector<std::string> *tokens;

    void enterHandler();
    void varsHandler();
    void printHandler();
    void compHandler();
    void joinHandler();
    void countLeafsHandler();
    void helpHandler();
    void showWarning(const std::string &msg);
    void showError(const std::string &msg);

  public:
    CmdInterface();
    ~CmdInterface();
    void commandHandler();

};

#endif
