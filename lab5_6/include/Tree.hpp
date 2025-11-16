#ifndef TREE_HPP
#define TREE_HPP

#include "Node.hpp"
#include "CmdStatus.hpp"
#include <string>

class Tree {
  private:
    Node* root;
    std::vector<Variable*> variables;

  public:
    std::string getVarsString();
    float compute(const std::vector<std::string> *tokens, CmdStatus &status);
    std::string toString();
    CmdStatus createTree(const std::vector<std::string> *tokens);
    ~Tree();
};
#endif
