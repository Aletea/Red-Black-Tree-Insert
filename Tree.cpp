#include <iostream>
#include <cstring>
#include "Node.h"
#include "Tree.h"

using namespace std;

Tree::Tree() {
  head = NULL;
}

Tree::~Tree() {
  head = NULL;
}

void Tree::insert(Node* newNode) {
  //start with head, go right/left
  if (head == NULL) {
    head = newNode;
    return;
  }
  Node* currentNode = head;
  while (currentNode != NULL) {
    if (currentNode->number > newNode->number) {
      if (currentNode->left == NULL) {
	currentNode->left = newNode;
	newNode->parent = currentNode;
	return;
      }
      currentNode = currentNode->left;
    }
    else {
      if (currentNode->right == NULL) {
	currentNode->right = newNode;
	newNode->parent = currentNode;
	return;
      }
      currentNode = currentNode->right;
    }
  }
}

//ERROR WHEN REMOVING HEAD NODE
void Tree::remove(int remNode) {
  if (head == NULL) {
    cout << "Tree is Empty" << endl;
    return;
  }
  Node* currentNode = head;
  //while not the right node
  while (currentNode->number != remNode) {
    //if the number is greater than the current node
    if (remNode > currentNode->number) {
      //if there is no right node, this number is not in the tree
      if (currentNode->right == NULL) {
	cout << "Number not found" << endl;
	return;
      }
      //otherwise, move right
      currentNode = currentNode->right;
    }
    //if number is less
    else {
      //if no left node, # not in tree 
      if (currentNode->left == NULL) {
	cout << "Number not found" << endl;
	return;
      }
      //otherwise, move right
      currentNode = currentNode->left;
    }
  }
  //get the node to replace the current Node that's being removed
  Node* replaceNode = NULL;
  //go to the right and then left to get the next node
  if (currentNode->right != NULL) {
    replaceNode = currentNode->right;
    while (replaceNode->left != NULL) {
      replaceNode = replaceNode->left;
    }
  }
  //or go to the left and then the right to get the next node
  else if (currentNode->left != NULL) {
    replaceNode = currentNode->left;
    while (replaceNode->right != NULL) {
      replaceNode = replaceNode->right;
    }
  }
  //if no left or right, just return
  else {
    //if parent
    if (currentNode->parent != NULL) {
      //if node is left node
      if (currentNode->parent->left == currentNode) {
	//set parent's left node to null
	currentNode->parent->left = NULL;
      }
      else {
	//otherwise, set parent's right to null
	currentNode->parent->right = NULL;
      }
    }
    //if current node is head, head is now null
    if (currentNode == head) {
      head = NULL;
    }
    currentNode = NULL;
    return;
  }
  //if the replacement node is a left node
  int leftNode = 0;
  if (replaceNode->parent->left == replaceNode) {
    //set that parent's left to null
    replaceNode->parent->left = NULL;
  }
  //otherwise, set parent's right to nukk
  else {
    leftNode = 1;
    replaceNode->parent->right = NULL;
  }
  //if replacement node has a right node
  if (replaceNode->right != NULL) {
    //if replaceNode is a left node
    if (leftNode == 0) {
      //set left node to replaceNode's right
      replaceNode->parent->left = replaceNode->right;
    }
    //if replaceNode is a rihgt node
    else {
      //set right node to replaceNode's right
      replaceNode->parent->right = replaceNode->right;
    }
  }
  else if (replaceNode->left != NULL) {
    if (leftNode == 0) {
      replaceNode->parent->left = replaceNode->left;
    }
    else {
      replaceNode->parent->right = replaceNode->left;
    }
  }
  //if current Node has a parent
  if (currentNode->parent != NULL) {
    //set the new node's parent to that node
    replaceNode->parent = currentNode->parent;
    //if currentNode is left node, set parent's left to replaceNode
    if (currentNode->parent->left == currentNode) {
      currentNode->parent->left = replaceNode;
    }
    //otherwise, set parent right to new node
    else {
      currentNode->parent->right = replaceNode;
    }
  }
  else {
    replaceNode->parent = NULL;
  }
  //if current node has a left, set replacenode's left
  if (currentNode->left != NULL) {
    replaceNode->left = currentNode->left;
    currentNode->left->parent = replaceNode;
  }
  //if current node has riht, set replaceNode's right
  if (currentNode->right != NULL) {
    replaceNode->right = currentNode->right;
    currentNode->right->parent = replaceNode;
  }
  //if currentNode is head, replaceNode is head
  if (currentNode == head) {
    head = replaceNode;
  }
}

//printNode should start as head
void Tree::display(Node* printNode, int height) {
  if (printNode->right != NULL) {
    int newHeight = height+1;
    display(printNode->right, newHeight);
  }
  for (int i = 0; i < height; i++) {
    cout << "\t";
  }
  cout << printNode->number << endl;
  if (printNode->left != NULL) {
    int newHeight = height+1;
    display(printNode->left, newHeight);
  }
}

Node* Tree::getHead() {
  return head;
}
