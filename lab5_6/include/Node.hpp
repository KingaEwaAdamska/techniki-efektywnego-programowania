#ifndef NODE_HPP
#define NODE_HPP

#include "StringHandler.hpp"
#include "Variable.hpp"
#include <string>
#include <vector>

struct Variable;
class Tree;

class Node {
public:
  virtual ~Node();
  virtual int getLeafAmount() = 0;
  virtual float getValue() = 0;
  virtual std::string toString() = 0;

  Node *getParent();

  static Result<Node *, Error>
  createNode(const std::vector<std::string> *tokens, int &actToken,
             std::vector<Variable *> *variables);

  Node(Node *parent = NULL);

private:
  Node *parent;
};

class OperatorNode : public Node {
  friend class Node;

public:
  ~OperatorNode();
  int getLeafAmount();
  void changeChild(Node *newChild);
  static void joinSubtreeRoot(Node *subtreeRoot, OperatorNode *actNode);

  OperatorNode(Node *parent = NULL);

protected:
  std::vector<Node *> childs;
};

class AdditionNode : public OperatorNode {
public:
  float getValue();
  std::string toString();

  AdditionNode(Node *parent = NULL);
};

class SubtractionNode : public OperatorNode {
public:
  float getValue();
  std::string toString();

  SubtractionNode(Node *parent = NULL);
};

class MultiplicationNode : public OperatorNode {
public:
  float getValue();
  std::string toString();

  MultiplicationNode(Node *parent = NULL);
};

class DivisionNode : public OperatorNode {
public:
  float getValue();
  std::string toString();

  DivisionNode(Node *parent = NULL);
};

class SinusNode : public OperatorNode {
public:
  float getValue();
  std::string toString();

  SinusNode(Node *parent = NULL);
};

class CosinusNode : public OperatorNode {
public:
  float getValue();
  std::string toString();

  CosinusNode(Node *parent = NULL);
};

class NumberNode : public Node {
public:
  float getValue();
  std::string toString();
  int getLeafAmount();

  NumberNode(float val, Node *parent = NULL);

private:
  float value;
};

class VarNode : public Node {
public:
  float getValue();
  std::string toString();
  int getLeafAmount();
  ~VarNode();

  VarNode(std::string varName, std::vector<Variable *> *variables,
          Node *parent = NULL);

private:
  Variable *var;
  std::vector<Variable *> *variables;
  Variable *addVariable(std::string var, std::vector<Variable *> *variables);
};

#endif
