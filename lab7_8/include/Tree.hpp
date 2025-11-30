#ifndef TREE_HPP
#define TREE_HPP

#include "Node.hpp"
#include <string>

class Tree {
  private:
    Node* root;
    std::vector<Variable*> variables;

  public:
    Result<void, Error> join(const std::vector<std::string> *tokens);
    Result<int, Error> countLeafs();
    Result<std::string, Error> getVarsString();
    Result<float, Error> compute(const std::vector<std::string> *tokens);
    std::string toString();
    Result<void, Error> createTree(const std::vector<std::string> *tokens);
    ~Tree();
};
#endif
