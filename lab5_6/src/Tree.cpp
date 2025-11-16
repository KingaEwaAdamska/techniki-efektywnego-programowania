#include "Tree.hpp"

CmdStatus Tree::createTree(std::vector<std::string> *tokens){
  if (root != NULL){
    delete root;
  }
  CmdStatus status;
  int actToken = 0;
  root = Node::createNode(tokens, actToken, status);

  return status;
}

float Tree::compute(){
  return root->getValue();
}

std::string Tree::toString(){
  return root->toString();
}

Tree::~Tree(){
  if (root != NULL){
    delete root;
  }
}
