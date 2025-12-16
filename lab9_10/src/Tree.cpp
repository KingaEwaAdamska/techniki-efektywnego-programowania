#include "Tree.hpp"
#include <iostream>
Tree::Tree(){
  root = NULL;
}

Tree::Tree(const Tree &other) {
  root = other.root ? other.root->clone() : NULL;
  std::cout << "kopia" << std::endl;
  variables.clear();
  for (const auto& var : other.variables) {
    variables.push_back(new Variable(*var));
  }
}

Tree::~Tree(){
  if (root != NULL){
    delete root;
    root = NULL;
  }
}

Tree Tree::operator=(const Tree &other) {
  if (this != &other) {
    if (root != NULL) {
      delete root;
    }
    
    root = other.root ? other.root->clone() : NULL;
    
    for (auto var : variables) {
      delete var;
    }
    
    variables.clear();
    for (const auto& var : other.variables) {
      variables.push_back(new Variable(*var));
    }
  }
  return *this;
}

Tree Tree::operator=(Tree &&other) {
  if (this != &other) {
    if (root != NULL) {
      delete root;
    }
    root = other.root;
    other.root = NULL;
    variables = std::move(other.variables);
  }
  return *this;
}

Result<Tree*, Error> Tree::createTree(const std::vector<std::string> *tokens){
  if (root != NULL){
    delete root;
    root = NULL;
  }
  variables.clear();
  int actToken = 0;
  Result<Node*, Error> createNodeRes = Node::createNode(tokens, actToken, &variables);
  
  if (!createNodeRes.isSuccess()) {
    return Result<Tree*, Error>::fail(createNodeRes.getErrors());
  }
  
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
  std::string varString;
  for (size_t i = 0; i < variables.size(); i++){
    varString += variables[i]->name + " ";
  }
  return Result<std::string, Error>::ok(varString);
}

Result<float, Error> Tree::compute(const std::vector<std::string> *tokens){
  if (root == NULL) {
    return Result<float, Error>::fail(new Error("There is no tree to compute"));
  }
  
  size_t varSize = variables.size();
  size_t tokensSize = tokens->size();
  Result<float, Error> res;
  
  if (varSize > tokensSize) {
    return Result<float, Error>::fail(new Error("You do not completed all the variables data"));
  } else if (tokensSize > varSize) {
    res.addError(new Error("You typed in too much data"));
  }
  
  for (size_t i = 0; i < varSize && i < tokensSize; i++) {
    std::string token = (*tokens)[i];
    if (!StringHandler::isNumber(token)){
      res.addError(new Error("invalid token: " + token + " instead used value: 0"));
      variables[i]->value = 0.0f;
    } else {
      variables[i]->value = StringHandler::stringToFloat(token);
    }
  }
  
  float value = root->getValue();
  res.addValue(value);
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

Tree Tree::operator+(const Tree &other) {
  Tree result = Tree(*this);
  
  if (root == NULL) {
    return result;
  }

  Node *subtreeRoot = other.root;

  OperatorNode* op = dynamic_cast<OperatorNode*>(result.root);
  if (op != NULL) {
    OperatorNode::joinSubtreeRoot(subtreeRoot, op);
  } else {
    Node *toDel = result.root;
    result.root = subtreeRoot;
    delete toDel;
  }
  return result;
}

Tree::Tree(Tree&& other) : root(other.root), variables(std::move(other.variables)) {
  other.root = NULL;
}

