#ifndef TNODE_H
#define TNODE_H
#include <iostream>
#include <string>
#include <map>

// abstract superclass of the syntax tree node
class TreeNode {
    
    TreeNode *leftChild = nullptr;
    TreeNode *rightChild = nullptr;
  protected:
    TreeNode *getLeftChild() const;
    TreeNode *getRightChild() const;
  public:
    std::string content;
    TreeNode(std::string cntt);
    std::string getContent() const;
    virtual bool evaluate(const std::map<std::string, bool> &assignment) const = 0; // pure virtual method
    void updateLeftChild(TreeNode *lChild); // for the operator "-", the operand is stored in leftChild
    void updateChildren(TreeNode *lChild, TreeNode *rChild);
    void print_chld();
    virtual ~TreeNode();

};

// concrete tree node of opertaor type
class OperatorNode : public TreeNode {
  public:
    OperatorNode(std::string cntt);
    bool evaluate(const std::map<std::string, bool> &assignment) const override;
};

// concrete tree node of constant type
class ConstantNode : public TreeNode {
  public:
    ConstantNode(std::string cntt);
    bool evaluate(const std::map<std::string, bool> &assignment) const override;
};

// concrete tree node of varibale type
class VariableNode : public TreeNode {
  public:
    VariableNode(std::string cntt);
    bool evaluate(const std::map<std::string, bool> &assignment) const override;
};

#endif
