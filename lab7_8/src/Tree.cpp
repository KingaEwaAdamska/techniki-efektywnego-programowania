#include "Tree.hpp"

Result<Tree*, Error> Tree::createTree(const std::vector<std::string> *tokens){
  if (root != NULL){
    delete root;
  }
  variables.clear();
  int actToken = 0;
  Result<Node*, Error> createNodeRes = Node::createNode(tokens, actToken, &variables);
  root = createNodeRes.getValue();
  Result<Tree*, Error> res(this);
  res.joinErrors(createNodeRes.getErrors());
  if (actToken < tokens->size()){
    res.addError(new Error("Your formula was too long"));
  }

  return res;
}

Result<int, Error> Tree::countLeafs() {
  if (root == NULL) {
    return Result<int, Error>::fail(new Error("There is no tree to count leafs, first enter tree"));
  }
  return Result<int, Error>::ok(root->getLeafAmount());
}

Result<std::string, Error> Tree::getVarsString(){
  int size = variables.size();
  std::string varString;
  for (int i = 0; i < size; i++){
    varString += variables[i]->name + " ";
  }
  return Result<std::string, Error>::ok(varString);
}

Result<float, Error> Tree::compute(const std::vector<std::string> *tokens){
  if (root == NULL) {
    return Result<float, Error>::fail(new Error("There is no tree to compute"));
  }
  int varSize = variables.size();
  int tokensSize = tokens->size();
  std::string token;
  Result<float, Error> res;
  if (varSize > tokensSize) {
    return Result<float, Error>::fail(new Error("You do not completed all the variables data"));
  } else if (tokensSize > varSize) {
    res.addError(new Error("You type in too much data"));
  }
  for (int i = 0; i < varSize; i++) {
    token = (*tokens)[i];
    if (!StringHandler::isNumber(token)){
      res.addError(new Error("invalid token: " + token + " instead used value: 0"));
    }
    variables[i]->value = StringHandler::stringToFloat(token);
  }
  res.addValue(root->getValue());
  return res;
}

Result<Tree*, Error> Tree::join(const std::vector<std::string> *tokens) {
  if (root == NULL) {
    return Result<Tree*, Error>::fail(new Error("There is no tree to join to"));
  }

  int actToken = 0;
  Result<Node*, Error> createNodeRes = Node::createNode(tokens, actToken, &variables);

  if (!createNodeRes.isSuccess()) return Result<Tree*, Error>::fail(createNodeRes.getErrors());

  Node *subtreeRoot = createNodeRes.getValue();

  Result<Tree*, Error> res(this);
  res.joinErrors(createNodeRes.getErrors());

  OperatorNode* op = dynamic_cast<OperatorNode*>(root);
  if (op != NULL) {
    OperatorNode::joinSubtreeRoot(subtreeRoot, op);
  } else {
    Node *toDel = root;
    root = subtreeRoot;
    delete toDel;
  }
  return res;
}

std::string Tree::toString(){
  if (root == NULL) {
    return "";
  }
  return root->toString();
}

Tree::~Tree(){
  if (root != NULL){
    delete root;
  }
}

template <>
std::string Result<Tree*, Error>::errorsToString() {
  std::string result = "Tree: ";
  if (_value && *_value) {
    result += (*_value)->toString() + "\n";
  } else {
    result += "NULL\n";
  }
  int size = _errors.size();
  for (int i = 0; i < size; i++) {
    if (!result.empty()) {
      result += "\n";
    }
    result += _errors[i]->toString();
  }
  return result;
}
 
