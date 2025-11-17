#include "Tree.hpp"

CmdStatus Tree::createTree(const std::vector<std::string> *tokens){
  if (root != NULL){
    delete root;
  }
  variables.clear();
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
  std::string token;
  if (varSize > tokensSize) {
    status.status = ERROR;
    status.msg = "You do not completed all the variables data";
    return 0.0;
  } else if (tokensSize > varSize) {
    status.status = WARNING;
    status.msg = "You type in too much data";
  }
  for (int i = 0; i < varSize; i++) {
    token = (*tokens)[i];
    if (!StringHandler::isNumber(token)){
      status.status = WARNING;
      status.msg += "invalid token: " + token + " instead used value: 0";
    }
    variables[i]->value = StringHandler::stringToFloat(token);
  }
  return root->getValue();
}

void Tree::join(const std::vector<std::string> *tokens, CmdStatus &status) {
  if (root == NULL) {
    status.status = ERROR;
    status.msg = "There is no tree to join to";
    return;
  }
  int actToken = 0;
  Node *subtreeRoot = Node::createNode(tokens, actToken, status, &variables);
  if (status.status == ERROR) return;
  OperatorNode* op = dynamic_cast<OperatorNode*>(root);
  if (op != NULL) {
    OperatorNode::joinSubtreeRoot(subtreeRoot, op);
  } else {
    Node *toDel = root;
    root = subtreeRoot;
    delete toDel;
  }
}

std::string Tree::toString(CmdStatus &status){
  if (root == NULL) {
    status.status = ERROR;
    status.msg = "There is no tree to show";
    return "";
  }
  return root->toString();
}

Tree::~Tree(){
  if (root != NULL){
    delete root;
  }
}
