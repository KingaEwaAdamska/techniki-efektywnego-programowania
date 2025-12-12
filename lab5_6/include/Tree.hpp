#ifndef TREE_HPP
#define TREE_HPP

#include "Node.hpp"
#include <string>

class Tree {
  private:
    Node* root;
    std::vector<Variable*> variables;

  public:
    void join(const std::vector<std::string> *tokens, CmdStatus &status);
    int countLeafs(CmdStatus &status);
    std::string getVarsString();
    float compute(const std::vector<std::string> *tokens, CmdStatus &status);
    std::string toString(CmdStatus &status);
    CmdStatus createTree(const std::vector<std::string> *tokens);
    ~Tree();
};
#endif
