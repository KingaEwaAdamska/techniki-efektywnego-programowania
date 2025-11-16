#include "Tree.hpp"

CmdStatus Tree::createTree(std::vector<std::string> *tokens){
  if (root != NULL){
    delete root;
  }
  CmdStatus status;
  int actToken = 0;
  root = Node::createNode(tokens, actToken, status, &variables);

  return status;
}

std::string Tree::getVarsString(){
  int size = variables.size();
  std::string varString;
  for (int i = 0; i < size; i++){
    varString += variables[i]->name + " ";
  }
  return varString;
}

float Tree::compute(){
  int varSize = variables.size();
  int tokensSize = tokens.size();
  if (variables.size() > tokens.size()){
    status = ERROR;
    msg = "You do not completed all the variables data";
    return 0.0;
  } else if (tokensSize > varSize){
    status = WARNING;
    msg = "You type in too much data";
  }
  for (int i = 0; i < varSize; i++){
    
  }
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
