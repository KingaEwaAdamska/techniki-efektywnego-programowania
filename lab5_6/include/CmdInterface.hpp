#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "Tree.hpp"
#include <string>
#include <vector>

class CmdInterface {
  private:
    Tree* tree;
    std::string command;
    std::vector<std::string> *tokens;

    Result<void, Error> enterHandler();
    Result<void, Error> varsHandler();
    Result<void, Error> printHandler();
    Result<void, Error> compHandler();
    Result<void, Error> joinHandler();
    Result<void, Error> countLeafsHandler();

    void helpHandler();
    void showWarning(const std::string &msg);
    void showError(const std::string &msg);

  public:
    CmdInterface();
    ~CmdInterface();
    void commandHandler();

};

#endif
