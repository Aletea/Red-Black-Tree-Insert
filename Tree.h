#ifndef TREE_H
#define TREE_H
#include "Node.h"
#include <iostream>

using namespace std;

class Tree {
 public:
  Tree();
  ~Tree();
  void insert(Node* newNode);
  void balance(Node* currentNode);
  int countBlacks(Node* root, int height);
  void display(Node* printNode, int height);
  Node* getHead();
  int checkEven(Node* current, Node* insert);
  void changeColor(Node* top);
  Node* traverse(Node* current);
  //int needChange(Node* current);
  //void fix(Node* current);
  
 private:
  Node* head;
  int leftHeight;
  int rightHeight;

};
#endif
