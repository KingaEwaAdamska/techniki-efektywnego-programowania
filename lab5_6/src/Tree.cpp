#include "Tree.hpp"

CmdStatus Tree::createTree(const std::vector<std::string> *tokens){
  if (root != NULL){
    delete root;
  }
  CmdStatus status;
  int actToken = 0;
  root = Node::createNode(tokens, actToken, status, &variables);

  if (actToken < tokens->size()){
    status.status = WARNING;
    status.msg = "Your formula was too long";
  }
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

float Tree::compute(const std::vector<std::string> *tokens, CmdStatus &status){
  status.status = SUCCESS;
  status.msg = "";
  int varSize = variables.size();
  int tokensSize = tokens->size();
  if (varSize > tokensSize){
    status.status = ERROR;
    status.msg = "You do not completed all the variables data";
    return 0.0;
  } else if (tokensSize > varSize){
    status.status = WARNING;
    status.msg = "You type in too much data";
  }
  for (int i = 0; i < varSize; i++){
    variables[i]->value = StringHandler::stringToFloat((*tokens)[i]);
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
