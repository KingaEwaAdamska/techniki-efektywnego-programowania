#ifndef INTERFACE_HPP
#define INTERFACE_HPP
#define LOG_FILE "log.txt"

#include "Tree.hpp"
#include <string>
#include <vector>
#include <unordered_map>

class CmdInterface {
  private:
    std::unordered_map<std::string, Tree*> trees;
    std::string currentTreeName;
    std::string command;
    std::vector<std::string> *tokens;

    void enterHandler();
    void varsHandler();
    void printHandler();
    void compHandler();
    void joinHandler();
    void countLeafsHandler();
    void helpHandler();
    void assignHandler();
    void listTreesHandler();
    void useHandler();
    void showWarning(const std::string &msg);
    void showError(const std::string &msg);
    
    bool isValidTreeName(const std::string& name);
    Tree* getCurrentTree();
    Tree* getTreeByName(const std::string& name);

  public:
    CmdInterface();
    ~CmdInterface();
    void commandHandler();

};

#endif
