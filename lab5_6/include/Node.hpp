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
    Node(Node *parent = NULL); 
    virtual ~Node();
    virtual Node* getLeaf() = 0;
    Node* getParent();
    virtual float getValue() = 0;
    virtual std::string toString() = 0;
    
    static Node* createNode(const std::vector<std::string> *tokens, int &actToken, CmdStatus &status, std::vector<Variable*> *variables);
};

class OperatorNode : public Node {
    friend class Node;
  protected:
    std::vector<Node*> childs;
  public:
    OperatorNode(Node *parent = NULL);
    ~OperatorNode();
    Node* getLeaf();
    void changeChild(Node *newChild);

    static void joinSubtreeRoot(Node *subtreeRoot, OperatorNode *actNode);
};

class AdditionNode : public OperatorNode {
  public:
    AdditionNode(Node *parent = NULL);
    float getValue();
    std::string toString();
};

class SubtractionNode : public OperatorNode {
  public:
    SubtractionNode(Node *parent = NULL);
    float getValue();
    std::string toString();
};

class MultiplicationNode : public OperatorNode {
  public:
    MultiplicationNode(Node *parent = NULL);
    float getValue();
    std::string toString();
};

class DivisionNode : public OperatorNode {
  public:
    DivisionNode(Node *parent = NULL);
    float getValue();
    std::string toString(); 
};

class SinusNode : public OperatorNode {
  public:
    SinusNode(Node *parent = NULL);
    float getValue();
    std::string toString();
};

class CosinusNode : public OperatorNode {
  public:
    CosinusNode(Node *parent = NULL);
    float getValue();
    std::string toString();
};

class NumberNode : public Node {
  private:
    float value;
  public:
    NumberNode(float val, Node *parent = NULL);
    float getValue();
    std::string toString();
    Node* getLeaf();
};

class VarNode : public Node {
  private: 
    Variable* var;
    std::vector<Variable*> *variables;
    Variable* addVariable(std::string var, std::vector<Variable*> *variables);
  public:
    float getValue();
    std::string toString();
    VarNode(std::string varName, std::vector<Variable*> *variables, Node *parent = NULL);
    ~VarNode();
    Node* getLeaf();
};

#endif
