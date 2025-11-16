#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "CmdStatus.hpp"
#include "Tree.hpp"
#include <string>
#include <vector>

class CmdInterface {
  private:
    Tree* tree;
    std::string command;
    std::vector<std::string> *tokens;

    CmdStatus enterHandler();
    CmdStatus varsHandler();
    CmdStatus printHandler();
    CmdStatus compHandler();
    CmdStatus joinHandler();
    void helpHandler();
    void showWarning(const std::string &msg);
    void showError(const std::string &msg);

  public:
    CmdInterface();
    ~CmdInterface();
    void commandHandler();

};

#endif
