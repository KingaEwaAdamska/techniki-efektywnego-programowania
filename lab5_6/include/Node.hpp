#ifndef NODE_HPP
#define NODE_HPP

#include "CmdStatus.hpp"
#include "StringHandler.hpp"
#include "Variable.hpp"
#include <string>
#include <vector>

struct Variable;
class Tree;

class Node {
  private:
    Node *parent;

  public:
    static Node* createNode(const std::vector<std::string> *tokens, int &actToken, CmdStatus &status, std::vector<Variable*> *variables);
    virtual float getValue() = 0;
    virtual std::string toString() = 0;
    
};

class OperatorNode : public Node {
    friend class Node;
  private:
    float childsNumber;
  protected:
    std::vector<Node*> childs;
  public:
    ~OperatorNode();

};

class AdditionNode : public OperatorNode {
  public:
    float getValue();
    std::string toString();
};

class SubtractionNode : public OperatorNode {
  public:
    float getValue();
    std::string toString();
};

class MultiplicationNode : public OperatorNode {
  public:
    float getValue();
    std::string toString();
};

class DivisionNode : public OperatorNode {
  public:
    float getValue();
    std::string toString(); 
};

class SinusNode : public OperatorNode {
  public:
    float getValue();
    std::string toString();
};

class CosinusNode : public OperatorNode {
  public:
    float getValue();
    std::string toString();
};

class NumberNode : public Node {
  private:
    float value;
  public:
    NumberNode(float val);
    float getValue();
    std::string toString();
};

class VarNode : public Node {
  private: 
    Variable* var;
    Variable* addVariable(std::string var, std::vector<Variable*> *variables);
  public:
    float getValue();
    std::string toString();
    VarNode(std::string varName, std::vector<Variable*> *variables);
};

#endif
