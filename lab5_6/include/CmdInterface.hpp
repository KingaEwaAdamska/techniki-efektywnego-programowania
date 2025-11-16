#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "CmdStatus.hpp"
#include "Tree.hpp"
#include <string>
#include <vector>

class CmdInterface {
  private:
    Tree* tree;
    std::string inputLine;
    std::string command;
    std::vector<std::string> tokens;

    void divideLineIntoTokens();
    CmdStatus enterHandler();
    CmdStatus varsHandler();
    CmdStatus printHandler();
    CmdStatus compHandler();
    CmdStatus joinHandler();
    void helpHandler();
    void showWarning(std::string msg);

  public:
    CmdInterface();
    ~CmdInterface();
    void commandHandler();

};

#endif
