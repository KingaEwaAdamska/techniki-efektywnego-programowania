#include "Node.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>

static bool isNumber(const std::string& str) {
    if (str.empty()) return false;
    
    for (size_t i = 0; i < str.length(); i++) {
        if (i == 0 && str[i] == '-' && str.length() > 1) continue;
        if (!isdigit(str[i])) return false;
    }
    return true;
}

static float stringToFloat(const std::string& str) {
    return atof(str.c_str());
}

// Node
Node* Node::createNode(std::vector<std::string> *tokens, int &actToken, CmdStatus &status) {
    Node *node = NULL;
    
    if (tokens->size() <= actToken) {
        status.status = WARNING;
        status.msg += "\nLack of tokens";
        return new NumberNode(1);
    }
    
    std::string token = (*tokens)[actToken];
    actToken++;
    
    if (isNumber(token)) {
        float value = stringToFloat(token);
        node = new NumberNode(value);
    } else if (token == "+") {
        AdditionNode *addNode = new AdditionNode();
        addNode->childs.push_back(createNode(tokens, actToken, status));
        addNode->childs.push_back(createNode(tokens, actToken, status));
        node = addNode;
    } else if (token == "-") {
        SubtractionNode *subNode = new SubtractionNode();
        subNode->childs.push_back(createNode(tokens, actToken, status));
        subNode->childs.push_back(createNode(tokens, actToken, status));
        node = subNode;
    } else if (token == "*") {
        MultiplicationNode *mulNode = new MultiplicationNode();
        mulNode->childs.push_back(createNode(tokens, actToken, status));
        mulNode->childs.push_back(createNode(tokens, actToken, status));
        node = mulNode;
    } else if (token == "/") {
        DivisionNode *divNode = new DivisionNode();
        divNode->childs.push_back(createNode(tokens, actToken, status));
        divNode->childs.push_back(createNode(tokens, actToken, status));
        node = divNode;
    } else if (token == "sin") {
        SinusNode *sinNode = new SinusNode();
        sinNode->childs.push_back(createNode(tokens, actToken, status));
        node = sinNode;
    } else if (token == "cos") {
        CosinusNode *cosNode = new CosinusNode();
        cosNode->childs.push_back(createNode(tokens, actToken, status));
        node = cosNode;
    } else {
        node = new VarNode(token);
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

VarNode::VarNode(std::string name){
  this->name = name;
}

float VarNode::getValue() {
  return 0;
}

std::string VarNode::toString() {
  return name;
}
