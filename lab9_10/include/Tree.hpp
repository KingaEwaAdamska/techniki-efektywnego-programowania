#pragma once
#include "Node.hpp"
#include <string>

class Tree {
  private:
    Node* root;
    std::vector<Variable*> variables;

  public:
    Tree();
    Tree(Tree&& other);
    Tree(const Tree &other);
    ~Tree();

    Result<Tree*, Error> createTree(const std::vector<std::string> *tokens);
    Result<Tree*, Error> join(const std::vector<std::string> *tokens);

    Result<int, Error> countLeafs();
    Result<std::string, Error> getVarsString();
    Result<float, Error> compute(const std::vector<std::string> *tokens);

    std::string toString();

    Tree operator=(const Tree &other);
    Tree operator+(const Tree &other);
    Tree operator=(Tree &&other);
};
 
