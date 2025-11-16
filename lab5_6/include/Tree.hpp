#ifndef TREE_HPP
#define TREE_HPP

#include "Node.hpp"
#include "CmdStatus.hpp"
#include <string>

class Tree {
  private:
    Node* root;
  
  public:
    float compute();
    std::string toString();
    CmdStatus createTree(std::vector<std::string> *tokens);
    ~Tree();
};
#endif
