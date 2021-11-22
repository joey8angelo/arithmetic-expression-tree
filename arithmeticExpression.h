#ifndef ARITHMETICEXPRESSION_H
#define ARITHMETICEXPRESSION_H
#include <iostream>
#include <cstdlib>

using namespace std;
struct TreeNode{
    char data;
    char key; // key is for the .dot file for visualization elsewhere
    TreeNode* left;
    TreeNode* right;
    TreeNode(char data, char key):data(data),key(key),left(0),right(0){}
};

class arithmeticExpression{
  private:
    string infixExpression;
    TreeNode* root;

  public:
    arithmeticExpression(const string &); // constructor
    ~arithmeticExpression(); // destructor
    void buildTree(); // converts infix notation to a tree
    void infix(); // prints in infix notation
    void prefix(); // prints in prefix notation
    void postfix(); // prints in postfix notation
    void visualizeTree(const string &); // generates dotty file for visualization of tree
    int evaluate(); // evaluates valid expression tree

 private:
    void removeAll(TreeNode*); // destructor helper
    int priority(char); // helper that determines the priority of given operators
    string infix_to_postfix(); // converts infix notation to postfix notation
    void infix(TreeNode *); // helper for infix
    void prefix(TreeNode *); // helper for prefix
    void postfix(TreeNode *); // helper for postfix
    bool isValidIntegerExpression(TreeNode *); // check if expression is valid to be evaluated
    int evaluateIntegerExpression(TreeNode *); // helper for evaluate
    void visualizeTree(ofstream &, TreeNode *); // helper for visualizeTree
};
#endif