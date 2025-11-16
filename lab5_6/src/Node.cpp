#include "Node.hpp"
#include <cmath>

// Node
Node* Node::createNode(const std::vector<std::string> *tokens, int &actToken, CmdStatus &status, std::vector<Variable*> *variables) {
  Node *node = NULL;
  
  if (tokens->size() <= actToken) {
    status.status = WARNING;
    status.msg += "\nLack of tokens";
    return new NumberNode(1);
  }
  
  std::string token = (*tokens)[actToken];
  actToken++;
  
  if (StringHandler::isNumber(token)) {
    float value = StringHandler::stringToFloat(token);
    node = new NumberNode(value);
  } else if (token == "+") {
    AdditionNode *addNode = new AdditionNode();
    addNode->childs.push_back(createNode(tokens, actToken, status, variables));
    addNode->childs.push_back(createNode(tokens, actToken, status, variables));
    node = addNode;
  } else if (token == "-") {
    SubtractionNode *subNode = new SubtractionNode();
    subNode->childs.push_back(createNode(tokens, actToken, status, variables));
    subNode->childs.push_back(createNode(tokens, actToken, status, variables));
    node = subNode;
  } else if (token == "*") {
    MultiplicationNode *mulNode = new MultiplicationNode();
    mulNode->childs.push_back(createNode(tokens, actToken, status, variables));
    mulNode->childs.push_back(createNode(tokens, actToken, status, variables));
    node = mulNode;
  } else if (token == "/") {
    DivisionNode *divNode = new DivisionNode();
    divNode->childs.push_back(createNode(tokens, actToken, status, variables));
    divNode->childs.push_back(createNode(tokens, actToken, status, variables));
    node = divNode;
  } else if (token == "sin") {
    SinusNode *sinNode = new SinusNode();
    sinNode->childs.push_back(createNode(tokens, actToken, status, variables));
    node = sinNode;
  } else if (token == "cos") {
    CosinusNode *cosNode = new CosinusNode();
    cosNode->childs.push_back(createNode(tokens, actToken, status, variables));
    node = cosNode;
  } else {
    node = new VarNode(token, variables);
  }
  
  return node;
}

// Operators
  OperatorNode::~OperatorNode() {
    for (float i = 0; i < childs.size(); i++) {
        delete childs[i];
    }
  }
  // +

  float AdditionNode::getValue(){
    return childs[0]->getValue() + childs[1]->getValue();
  }

  std::string AdditionNode::toString(){
    return " + " + childs[0]->toString() + " " + childs[1]->toString();
  }

  // -

  float SubtractionNode::getValue(){
    return childs[0]->getValue() - childs[1]->getValue();
  }

  std::string SubtractionNode::toString(){
    return " - " + childs[0]->toString() + " " + childs[1]->toString();
  }

  // *

  float MultiplicationNode::getValue(){
    return childs[0]->getValue() * childs[1]->getValue();
  }

  std::string MultiplicationNode::toString(){
    return " * " + childs[0]->toString() + " " + childs[1]->toString();
  }

  // /

  float DivisionNode::getValue(){
    return childs[0]->getValue() / childs[1]->getValue();
  }

  std::string DivisionNode::toString(){
    return " / " + childs[0]->toString() + " " + childs[1]->toString();
  }

  // sin

  float SinusNode::getValue(){
    return std::sin(childs[0]->getValue());
  }

  std::string SinusNode::toString(){
    return " sin " + childs[0]->toString();
  }

  // cos

  float CosinusNode::getValue(){
    return std::cos(childs[0]->getValue());
  }

  std::string CosinusNode::toString(){
    return " cos " + childs[0]->toString();
  }



// Number

NumberNode::NumberNode(float val){
  value = val;
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

VarNode::VarNode(std::string varName, std::vector<Variable*> *variables){
  var = addVariable(varName, variables);
}

float VarNode::getValue() {
  return var->value;
}

std::string VarNode::toString() {
  return var->name;
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
