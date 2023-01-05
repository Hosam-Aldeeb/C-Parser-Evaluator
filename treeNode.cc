#include "treeNode.h"

TreeNode::TreeNode(std::string cntt): content {cntt} {}

std::string TreeNode::getContent() const {
  return content;
}

TreeNode *TreeNode::getLeftChild() const {
  // your code starts here
  return leftChild;
}
TreeNode *TreeNode::getRightChild() const {
  // your code starts her
  return rightChild;
}

void TreeNode::updateLeftChild(TreeNode *lChild) {
  // your code starts here
  //get left child from line 9, then assist lchild to it

  leftChild =lChild;

}

void TreeNode::updateChildren(TreeNode *lChild, TreeNode *rChild) {
  // your code starts here
  leftChild=lChild;
  rightChild=rChild;
}

void TreeNode::print_chld()
{
  TreeNode *l__Child = TreeNode::getLeftChild();
  TreeNode *r__Child = TreeNode::getRightChild();
 // std::cout << getContent() << std::endl;

  if (l__Child != nullptr)
  {
    l__Child->print_chld();
  }
  if (r__Child != nullptr)
  {
    r__Child->print_chld();
  }
}

OperatorNode::OperatorNode(std::string cntt): TreeNode{cntt} {}

bool OperatorNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here
  //fuction for different operstors
  //returining the value after the assignment
  if (content=="+"){
    bool leftC=getLeftChild()->evaluate(assignment);
    bool rightC=getRightChild()->evaluate(assignment);
    return leftC||rightC;
  }
  if(content=="*"){
    bool leftC=getLeftChild()->evaluate(assignment);
    bool rightC=getRightChild()->evaluate(assignment);
    return leftC && rightC;
  }
  if (content =="-"){
    bool leftC=getLeftChild()->evaluate(assignment);
    return leftC;
  }
  

  return false;
}

ConstantNode::ConstantNode(std::string cntt): TreeNode{cntt} {}

bool ConstantNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here convert string to int first
  //0,1
  if (content=="0"){
    bool zero=stoi(content);
    return zero;
  }
  if (content=="1"){
    bool one=stoi(content);
      return one;
      //std::cout<<one;
    }
  
  return false;
}

VariableNode::VariableNode(std::string cntt): TreeNode{cntt} {}

bool VariableNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here
  // std::cout<<assignment.at(content);
  return assignment.at(content);

}

TreeNode::~TreeNode() {
  // your code starts here
  //to delete left and right
}
