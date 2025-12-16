#include "Node.hpp"
#include <cmath>

// Node
Node::Node(Node *parent){
  this->parent = parent;
}

Node::~Node() {}

Node* Node::getParent(){
  return parent;
}

Result<Node*, Error> Node::createNode(const std::vector<std::string> *tokens, int &actToken, std::vector<Variable*> *variables) {
  Node *node = NULL;
  
  Result<Node*, Error> finalRes;

  if (tokens->size() <= actToken) {
    finalRes.addError(new Error("Lack of tokens"));
    finalRes.addValue(new NumberNode(1));
    return finalRes;
  }
  
  std::string token = (*tokens)[actToken];
  actToken++;
  
  if (StringHandler::isNumber(token)) {
    float value = StringHandler::stringToFloat(token);
    node = new NumberNode(value);
  } else if (token == "+" || token == "-" || token == "*" || token == "/") {
    Result<Node*, Error> res1 = createNode(tokens, actToken, variables);
    Result<Node*, Error> res2 = createNode(tokens, actToken, variables);

    finalRes.joinErrors(res1);
    finalRes.joinErrors(res2);

    if (token == "+") {
      AdditionNode *addNode = new AdditionNode();
      addNode->childs.push_back(res1.getValue());
      addNode->childs.push_back(res2.getValue());
      node = addNode;
    } else if (token == "-") {
      SubtractionNode *subNode = new SubtractionNode();
      subNode->childs.push_back(res1.getValue());
      subNode->childs.push_back(res2.getValue());
      node = subNode; 
    } else if (token == "*") {
      MultiplicationNode *mulNode = new MultiplicationNode();
      mulNode->childs.push_back(res1.getValue());
      mulNode->childs.push_back(res2.getValue());
      node = mulNode;
    } else if (token == "/") {
      DivisionNode *divNode = new DivisionNode();
      divNode->childs.push_back(res1.getValue());
      divNode->childs.push_back(res2.getValue());
      node = divNode;
    }

  } else if (token == "sin" || token == "cos") {
    Result<Node*, Error> res = createNode(tokens, actToken, variables);

    finalRes.joinErrors(res);

    if (token == "sin"){
      SinusNode *sinNode = new SinusNode();
      sinNode->childs.push_back(res.getValue());
      node = sinNode;
    } else if (token == "cos") {
      CosinusNode *cosNode = new CosinusNode();
      cosNode->childs.push_back(res.getValue());
      node = cosNode;
    }
  } else {
    node = new VarNode(token, variables);
  }
  
  finalRes.addValue(node);
  return finalRes;
}

// Operators

OperatorNode::OperatorNode(Node *parent) : Node(parent) {}

OperatorNode::~OperatorNode() {
  for (float i = 0; i < childs.size(); i++) {
      delete childs[i];
  }
}

int OperatorNode::getLeafAmount() {
  int leafs = 0;
  int childsSize = childs.size();
  for (int i = 0; i < childsSize; i++) {
    leafs += childs[i]->getLeafAmount();
  }
  return leafs; 
}

void OperatorNode::changeChild(Node *newChild){
  Node *childToDel = childs[0];
  childs[0] = newChild;
  delete childToDel;
}

void OperatorNode::joinSubtreeRoot(Node *subtreeRoot, OperatorNode *actNode){
  Node *node = actNode->childs[0];
  OperatorNode* op = dynamic_cast<OperatorNode*>(node);
  if (op != NULL) {
    OperatorNode::joinSubtreeRoot(subtreeRoot, op);
  } else {
    Node *toDel = node;
    actNode->childs[0] = subtreeRoot;
    delete toDel;
  }
}

  // +

AdditionNode::AdditionNode(Node *parent) : OperatorNode(parent) {}

float AdditionNode::getValue(){
  return childs[0]->getValue() + childs[1]->getValue();
}

std::string AdditionNode::toString(){
  return " + " + childs[0]->toString() + " " + childs[1]->toString();
}

  // -

SubtractionNode::SubtractionNode(Node *parent) : OperatorNode(parent) {}

float SubtractionNode::getValue(){
  return childs[0]->getValue() - childs[1]->getValue();
}

std::string SubtractionNode::toString(){
  return " - " + childs[0]->toString() + " " + childs[1]->toString();
}

  // *

MultiplicationNode::MultiplicationNode(Node *parent) : OperatorNode(parent) {}

float MultiplicationNode::getValue(){
  return childs[0]->getValue() * childs[1]->getValue();
}

std::string MultiplicationNode::toString(){
  return " * " + childs[0]->toString() + " " + childs[1]->toString();
}

  // /

DivisionNode::DivisionNode(Node *parent) : OperatorNode(parent) {}

float DivisionNode::getValue(){
  return childs[0]->getValue() / childs[1]->getValue();
}

std::string DivisionNode::toString(){
  return " / " + childs[0]->toString() + " " + childs[1]->toString();
}

  // sin

SinusNode::SinusNode(Node *parent) : OperatorNode(parent) {}

float SinusNode::getValue(){
  return std::sin(childs[0]->getValue());
}

std::string SinusNode::toString(){
  return " sin " + childs[0]->toString();
}

  // cos

CosinusNode::CosinusNode(Node *parent) : OperatorNode(parent) {}

float CosinusNode::getValue(){
  return std::cos(childs[0]->getValue());
}

std::string CosinusNode::toString(){
  return " cos " + childs[0]->toString();
}



// Number

NumberNode::NumberNode(float val, Node *parent) : Node(parent){
  value = val;
}

int NumberNode::getLeafAmount() {
  return 1;
}

float NumberNode::getValue(){
  return value;
}

std::string NumberNode::toString() {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

// Var
VarNode::VarNode(std::string varName, std::vector<Variable*> *variables, Node *parent) 
  : Node(parent), var(addVariable(varName, variables)) {
  this->variables = variables;
}

VarNode::~VarNode() {
  var->occurrings--;
  if (var->occurrings == 0) {
    for (std::vector<Variable*>::iterator it = variables->begin();
         it != variables->end(); )
    {
        if (*it == var) {
            delete *it;
            it = variables->erase(it);
            var = NULL;
            return;
        } else {
            ++it;
        }
    }
  }
}

float VarNode::getValue() {
  return var->value;
}

std::string VarNode::toString() {
  return var->name;
}

int VarNode::getLeafAmount() {
  return 1;
}

Variable* VarNode::addVariable(std::string var, std::vector<Variable*> *variables) {
  int size = variables->size();
  std::string varString;
  Variable *actVar = NULL;
  for (int i = 0; i < size; i++){
    actVar = (*variables)[i];
    if (actVar->name == var){
      actVar->occurrings++; 
      return actVar;
    }
  }
  variables->push_back(new Variable(var));
  return (*variables)[size];
}

Node* Node::clone() const {
  return nullptr; 
}

// OperatorNode
Node* OperatorNode::clone() const {
  return nullptr; 
}

// AdditionNode
Node* AdditionNode::clone() const {
  AdditionNode* newNode = new AdditionNode(nullptr);
  for (size_t i = 0; i < childs.size(); i++) {
    newNode->childs.push_back(childs[i]->clone());
  }
  return newNode;
}

// SubtractionNode
Node* SubtractionNode::clone() const {
  SubtractionNode* newNode = new SubtractionNode(nullptr);
  for (size_t i = 0; i < childs.size(); i++) {
    newNode->childs.push_back(childs[i]->clone());
  }
  return newNode;
}

// MultiplicationNode
Node* MultiplicationNode::clone() const {
  MultiplicationNode* newNode = new MultiplicationNode(nullptr);
  for (size_t i = 0; i < childs.size(); i++) {
    newNode->childs.push_back(childs[i]->clone());
  }
  return newNode;
}

// DivisionNode
Node* DivisionNode::clone() const {
  DivisionNode* newNode = new DivisionNode(nullptr);
  for (size_t i = 0; i < childs.size(); i++) {
    newNode->childs.push_back(childs[i]->clone());
  }
  return newNode;
}

// SinusNode
Node* SinusNode::clone() const {
  SinusNode* newNode = new SinusNode(nullptr);
  for (size_t i = 0; i < childs.size(); i++) {
    newNode->childs.push_back(childs[i]->clone());
  }
  return newNode;
}

// CosinusNode
Node* CosinusNode::clone() const {
  CosinusNode* newNode = new CosinusNode(nullptr);
  for (size_t i = 0; i < childs.size(); i++) {
    newNode->childs.push_back(childs[i]->clone());
  }
  return newNode;
}

// NumberNode
Node* NumberNode::clone() const {
  return new NumberNode(value, nullptr);
}

// VarNode
Node* VarNode::clone() const {
  VarNode* newNode = new VarNode(var->name, variables, nullptr);
  newNode->var = this->var;
  var->occurrings++;
  return newNode;
}
