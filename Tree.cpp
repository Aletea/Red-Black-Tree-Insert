
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
  //if head empty, fill head and set to black, then return
  if (head == NULL) {
    head = newNode;
    newNode->color = 1;
    return;
  }
  Node* currentNode = head;
  while (currentNode != NULL) {
    if (currentNode->number > newNode->number) {
      if (currentNode->left == NULL) {
	currentNode->left = newNode;
	newNode->parent = currentNode;
	
	balance(newNode);
	
	
	return;
      }
      currentNode = currentNode->left;
    }
    else {
      if (currentNode->right == NULL) {
	currentNode->right = newNode;
	newNode->parent = currentNode;
	
	balance(newNode);
	
	
	return;
      }
      currentNode = currentNode->right;
    }
  }
}

void Tree::balance(Node* currentNode) {
  Node* insertNode = currentNode;
  //get uncle
  Node* uncle = NULL;
  if (currentNode->parent == head) {
    return;
  }
  if (currentNode->parent->parent->left == currentNode->parent) {
    uncle = currentNode->parent->parent->right;
  }
  else {
    uncle = currentNode->parent->parent->left; 
  }
  //get grandparent
  Node* grandparent = currentNode->parent->parent;
  
  //if uncle  is null, shift tree
  //get side of currentNode
  //subtract height by one
  //get new height on the side the new node was entered
  if (uncle == NULL) {
    //if parent is on left side
    if (currentNode->parent->parent->left == currentNode->parent) {
    //move current node to left side of parent
      if (currentNode->parent->left != currentNode) {
	//SWITCH PARENT AND CURRENT NODE
	grandparent->left = currentNode;
	currentNode->left = currentNode->parent;
	currentNode->parent->parent = currentNode;
	currentNode->parent->right = NULL;
	//get parent before resetting current Node's parent
	Node* newCurrent = currentNode->parent;
	currentNode->parent = grandparent;
	//swap color
	int currentColor = currentNode->color;
	currentNode->color = newCurrent->color;
	newCurrent->color = currentColor;
	//set new currentNode
	currentNode = newCurrent;
      }
    //make parent grandparent
      if (grandparent->parent != NULL) {
      if (grandparent->parent->right == grandparent) {
	grandparent->parent->right = currentNode->parent;
      }
      else {
	grandparent->parent->left = currentNode->parent;
      }
      }
      else {
	//if grandparent is head, set parent to head
	head = currentNode->parent;
      }
      currentNode->parent->parent = grandparent->parent;
      grandparent->parent = currentNode->parent;
      currentNode->parent->right = grandparent;
      //set grandparent's left and right to NULL
      grandparent->right = NULL;
      grandparent->left = NULL;
    }
    //if parent on right side
    else {
    //move current node to right side of parent
      if (currentNode->parent->right != currentNode) {
	//SWITCH PARENT AND CURRENT NODE
	grandparent->right = currentNode;
	currentNode->parent->parent = currentNode;
	currentNode->right = currentNode->parent;
	currentNode->parent->left = NULL;
	//get parent before resetting current Node's parent
	Node* Parent = currentNode->parent;
	currentNode->parent = grandparent;
	//recolor
	int swapColor = currentNode->color;
	currentNode->color = Parent->color;
	Parent->color = swapColor;
	//reset current node
	currentNode = Parent;
	
      }
      //make parent grandparent
      if (grandparent->parent != NULL) {
	if (grandparent->parent->left == grandparent) {
	  grandparent->parent->left = currentNode->parent;
	}
	else {
	  grandparent->parent->right = currentNode->parent;
	}
      }
      //if grandparent is head, set parent to head
      else {
	head = currentNode->parent;
      }
      currentNode->parent->parent = grandparent->parent;
      grandparent->parent = currentNode->parent;
      currentNode->parent->left = grandparent;
      grandparent->right = NULL;
      grandparent->left = NULL;
    }
    //RECOLOR
    int parentColor = currentNode->parent->color;
    currentNode->parent->color = grandparent->color;
    grandparent->color = parentColor;
    currentNode->color = grandparent->color;
  }
  //Case 3
  //if parent and uncle are red
  if (uncle != NULL) {
  if (currentNode->parent->color == 0 && uncle->color == 0) {
  
    
    if (grandparent->parent != NULL) {
      if (grandparent->parent->color == 0) {
	currentNode->color = 1;
      }
    }
    if (currentNode->color != 1) {
    uncle->color = 1;
    currentNode->parent->color = 1;
    //set grandparent to red
    grandparent->color = 0;
    if (grandparent == head) {
      
      grandparent->color = 1;
    }
    }
    
  }
  }
  //Case 4
  //if the parent is red and the uncle is black

  if (uncle != NULL) {
    if (currentNode->parent->color == 0 && uncle->color == 1) {
  
    //if parent on left side
    if (currentNode->parent->parent->left == currentNode->parent) {
      //move node to outside
      if (currentNode->parent->left != currentNode) {
	//SWITCH PARENT AND CURRENT NODE
	grandparent->left = currentNode;
	currentNode->parent->parent = currentNode;
	currentNode->parent->right = NULL;
	currentNode->left = currentNode->parent;
	//get parent before resetting current node's parent
	Node* Parent = currentNode->parent;
	currentNode->parent = grandparent;
	//recolor
	int swapColor = currentNode->color;
	currentNode->color = Parent->color;
	Parent->color = swapColor;
	//reset currentNode
	currentNode = Parent;
	
      }
      //set parent to grandparent
      //set grandparent's parent's child to parent
      if (grandparent->parent != NULL) {
	if (grandparent->parent->left == grandparent) {
	grandparent->parent->left = currentNode->parent;
      }
      else {
	grandparent->parent->right = currentNode->parent;
      }
      }
      //if granparent is head, reset head
      else {
	head = currentNode->parent;
      }
      //set parent's parent to gparent's parent
      currentNode->parent->parent = grandparent->parent;
      //set gparent's parent to parent
      grandparent->parent = currentNode->parent;
      //set parent's child tp gparent
      currentNode->parent->right = grandparent;
      //set gparent's left to NULL
      grandparent->left = NULL;
    }
    //if parent on right side
    else {
      //move node to outside
      if (currentNode->parent->right != currentNode) {
	//SWITCH PARENT AND CURRENT NODE
	grandparent->right = currentNode;
	currentNode->parent->parent = currentNode;
	currentNode->right = currentNode->parent;
	currentNode->parent->left = NULL;
	//get parent before resetting currentNode's parent
	Node* Parent = currentNode->parent;
	currentNode->parent = grandparent;
	//recolor
	int swapColor = currentNode->color;
	currentNode->color = Parent->color;
	Parent->color = swapColor;
	//reset current node
	currentNode = Parent;
      }
      //set parent to grandparent
      //set grandparent's parent's child to parent
      if (grandparent->parent != NULL) {
	if (grandparent->parent->left = grandparent) {
	  grandparent->parent->left = currentNode->parent;
	}
	else {
	  grandparent->parent->right = currentNode->parent;
	}
      }
      else {
	head = currentNode->parent;
      }
      //set parent's parent to gparent's parent
      currentNode->parent->parent = grandparent->parent;
      //set gparent's parent to parent
      grandparent->parent = currentNode->parent;
      //set parent's child to grandparent
      currentNode->parent->left = grandparent;
      //set gparent's right to NULL
      grandparent->right = NULL;
    }
    //recolor
    currentNode->parent->color = 1;
    grandparent->color = 0;
  }
  }

  //count black nodes on each side
  int rightBlacks;
  if (head == NULL) {
    rightBlacks = 0;
  }
  else if (head->right == NULL) {
    rightBlacks = 1;
  }
  else {
    rightBlacks = countBlacks(head->right, 0);
  }
    int leftBlacks;
    if (head == NULL) {
    leftBlacks = 0;
    }
    else if (head->left == NULL) {
      leftBlacks = 1;
    }
    else {
      leftBlacks = countBlacks(head->left, 0);
    }
    //cout << "Left: " << leftBlacks << endl;
    //cout << "Right: " << rightBlacks << endl;
  //CHECK EVEN RIGHT AND LEFT
    int even = checkEven(head, insertNode);
    if (even == 0 && insertNode->color == 1) {
      //cout << "Even: " << endl;
      //display(head,1);
      //find inserted left or right
      Node* findHead = insertNode;
      while (findHead->parent != head) {
	findHead = findHead->parent;
      }
      if (findHead->parent->right == findHead) {
	changeColor(head->right);
      }
      else {
	changeColor(head->left);
      }
      return;
    }
    //CHECK EVEN ONE SIDE
    //CHECK THAT RIGHT AND LEFT SIDE ARE BALANCED
  if (leftBlacks > rightBlacks) {
    //shift to right side
    Node* replaceNode = head->left;
    while (replaceNode->right != NULL) {
      replaceNode = replaceNode->right;
    }
    replaceNode->parent->right = NULL;
    if (replaceNode->left != NULL) {
      replaceNode->parent->right = replaceNode->left;
      replaceNode->left->parent = replaceNode->parent;
      replaceNode->left = NULL;
      if (replaceNode->parent->color == 0) {
	replaceNode->parent->right->color = 1;
      }
      else {
	replaceNode->parent->right->color = 0;
      }
      //check the Node whose color you just changed's nodes
      Node* checkNode = replaceNode->parent->right;
      if (checkNode->left != NULL) {
	if (checkNode->color == 0) {
	  checkNode->left->color = 1;
	}
	else {
	  checkNode->left->color = 0;
	}
      }
      if (checkNode->right != NULL) {
	if (checkNode->color == 0) {
	  checkNode->right->color = 1;
	}
	else {
	  checkNode->right->color = 0;
	}
      }
    }
    replaceNode->parent = NULL;
    replaceNode->right = head;
    head->parent = replaceNode;
    replaceNode->left = head->left;
    head->left->parent = replaceNode;
    replaceNode->right = head->right;
    head->right->parent = replaceNode;
    leftHeight = leftHeight-1;
    replaceNode->color = 1;
    head->right = NULL;
    head->left = NULL;
    //move head
    Node* moveHead = replaceNode->right;
    while (moveHead->left != NULL) {
      moveHead = moveHead->left;
    }
    moveHead->left = head;
    head->parent = moveHead;
    //balance for head
    head->color = 0;
    if (head->parent->color == 0) {
      head->color = 1;
    }
    Node* headNode = head;
    head = replaceNode;
    //display(head, 1);
    //BALANCE LEFT SIDE, SHIFT ALL NODES UP
    Node* current = head->left;
    while (current->right == NULL) {
      //cout << "Switching" << endl;
      //make their left node their right's furthest left Node
      //move down the tree one (reset current)
      if (current->left == NULL) {
	//cout << "Switch terminated" << endl;
	break;
      }
      Node* replaceNode2 = current->left;
      while (replaceNode2->right != NULL) {
	replaceNode2 = replaceNode2->right;
      }
      if (replaceNode2->left != NULL) {
	replaceNode2->left->parent = replaceNode2->parent;
	if (replaceNode2 == current->left) {
	  replaceNode2->parent->left = replaceNode2->left;
	  if (replaceNode2->parent->color == 0) {
	    replaceNode2->parent->left->color = 1;
	  }
	  else {
	    replaceNode2->parent->left->color = 0;
	  }
	}
	else {
	replaceNode2->parent->right = replaceNode2->left;
	replaceNode2->left->color = replaceNode2->color;
	}
	replaceNode2->left = NULL;
      }
      replaceNode2->parent->right = NULL;
      replaceNode2->parent = current->parent;
      current->parent->left = replaceNode2;
      if (current->left != replaceNode2) {
	current->left->parent = replaceNode2;
	replaceNode2->left = current->left;
      }
      current->left = NULL;
      current->parent = replaceNode2;
      replaceNode2->right = current;
      replaceNode2->color = current->color;
      if (replaceNode2->color == 0) {
	current->color = 1;
      }
      else {
	current->color = 0;
      }
      if (replaceNode2->left == NULL) {
	break;
      }
      current = replaceNode2->left;
      //display(head,1);
    }
    balance(headNode);

  }
  if (rightBlacks > leftBlacks) {
    //shift to left side
    //shift to right side
    //get replacement node
    Node* replaceNode = head->right;
    while (replaceNode->left != NULL) {
      replaceNode = replaceNode->left;
    }
    //remove parent replationship
    replaceNode->parent->left = NULL;
    //if replacenode has a right node, move it up
    if (replaceNode->right != NULL) {
      replaceNode->parent->left = replaceNode->right;
      replaceNode->right->parent = replaceNode->parent;
      replaceNode->right = NULL;
      if (replaceNode->parent->color == 0) {
	replaceNode->parent->left->color = 1;
      }
      else {
	replaceNode->parent->left->color = 0;
      }
      //check the Node whose color you just changed's nodes
      Node* checkNode = replaceNode->parent->left;
      if (checkNode->left != NULL) {
	if (checkNode->color == 0) {
	  checkNode->left->color = 1;
	}
	else {
	  checkNode->left->color = 0;
	}
      }
      if (checkNode->right != NULL) {
	if (checkNode->color == 0) {
	  checkNode->right->color = 1;
	}
	else {
	  checkNode->right->color = 0;
	}
      }
    }
    replaceNode->parent = NULL;
    replaceNode->right = head->right;
    head->left->parent = replaceNode;
    replaceNode->left = head->left;
    head->right->parent = replaceNode;
    rightHeight = rightHeight-1;
    replaceNode->color = 1;
    head->right = NULL;
    head->left = NULL;
    //move head
    Node* moveHead = replaceNode->left;
    while (moveHead->right != NULL) {
      moveHead = moveHead->right;
    }
    moveHead->right = head;
    head->parent = moveHead;
    //balance for head
    head->color = 0;
    Node* headNode = head;
    head = replaceNode;
    //display(head, 1);
    //SHIFT ALL RIGHT NODES UP
    Node* current = head->right;
    while (current->left == NULL) {
      //cout << "Switching" << endl;
      //make their left node their right's furthest left Node
      //move down the tree one (reset current)
      if (current->right == NULL) {
	//cout << "Switch terminated" << endl;
	break;
      }
      Node* replaceNode2 = current->right;
      while (replaceNode2->left != NULL) {
	replaceNode2 = replaceNode2->left;
      }
      if (replaceNode2->right != NULL) {
	replaceNode2->right->parent = replaceNode2->parent;
	if (replaceNode2 == current->right) {
	  replaceNode2->parent->right = replaceNode2->right;
	  if (replaceNode2->parent->color == 0) {
	    replaceNode2->parent->right->color = 1;
	  }
	  else {
	    replaceNode2->parent->right->color = 0;
	  }
	}
	else {
	replaceNode2->parent->left = replaceNode2->right;
	replaceNode2->right->color = replaceNode2->color;
	}
	replaceNode2->right = NULL;
      }
      replaceNode2->parent->left = NULL;
      replaceNode2->parent = current->parent;
      current->parent->right = replaceNode2;
      if (current->right != replaceNode2) {
	current->right->parent = replaceNode2;
	replaceNode2->right = current->right;
      }
      current->right = NULL;
      current->parent = replaceNode2;
      replaceNode2->left = current;
      replaceNode2->color = current->color;
      if (replaceNode2->color == 0) {
	current->color = 1;
      }
      else {
	current->color = 0;
      }
      if (replaceNode2->right == NULL) {
	break;
      }
      current = replaceNode2->right;
      //display(head,1);
    }
    balance(headNode);
  }
  //traverse through tree and fix balance points
  bool traversing = true;
  while (traversing == true) {
    Node* find = traverse(head);
    if (find == NULL) {
      break;
    }
    else {
      //cout << "Found" << endl;
      balance(find);
    }
  }
  /*Node* checkChange = head;
  if (checkChange != NULL) {
    if (currentNode->color == 1 && (currentNode->parent->left == NULL || currentNode->parent->right == NULL)) {
      Node* getSide = currentNode;
      while (getSide->parent != head) {
	getSide = getSide->parent;
      }
      changeColor(getSide); 
    }
    }*/
  //check for need for color change
  int checkChange = needChange(head);
  if (checkChange == 1) {
    changeColor(head->right);
  }
  if (checkChange == 2) {
    changeColor(head->left);
  }
  checkChange = needChange(head);
  if (checkChange == 1) {
    changeColor(head->right);
  }
  if (checkChange == 2) {
    changeColor(head->left);
  }
  if (currentNode->left == NULL && currentNode->right == NULL) {
    if (currentNode->color == 1 && (currentNode->parent->right == NULL || currentNode->parent->left == NULL)) {
      Node* getSide = currentNode;
      while (getSide->parent != head) {
	getSide = getSide->parent;
      }
      if (getSide->parent->left == getSide) {
	changeColor(head->left);
      }
      else {
	changeColor(head->right);
      }
    }
  }
  //rotate tree if one side is 2x height
  Node* rotateNode = findRotation(head);
  while (rotateNode != NULL) {  
    if (rotateNode != NULL) {
      fixReds(head);
    checkChange = needChange(head);
    //cout << "Check Change: " << checkChange;
    if (checkChange == 1) {
      changeColor(head->right);
    }
    if (checkChange == 2) {
      changeColor(head->left);
    }
    checkChange = needChange(head);
    //cout << "Check Change: " << checkChange;
    if (checkChange == 1) {
      changeColor(head->right);
    }
    if (checkChange == 2) {
      changeColor(head->left);
    }
    }
    //cout << "current2: " << endl;
    //display(head,0);
    rotateNode = findRotation(head);
    //cout << "current3" << endl;
    //display(head,0);
    fixReds(head);
    if (rotateNode != NULL) {
      if (findRotation(head) == NULL) {
	break;
      }
    }
  }
  //check for need for color change
  checkChange = needChange(head);
  if (checkChange == 1) {
    changeColor(head->right);
  }
  if (checkChange == 2) {
    changeColor(head->left);
  }
  checkChange = needChange(head);
  if (checkChange == 1) {
    changeColor(head->right);
  }
  if (checkChange == 2) {
    changeColor(head->left);
  }
  checkChange = needChange(head);
  if (checkChange == 1) {
    changeColor(head->right);
  }
  if (checkChange == 2) {
    changeColor(head->left);
  }
  if (currentNode->left == NULL && currentNode->right == NULL) {
    if (currentNode->color == 1 && (currentNode->parent->right == NULL || currentNode->parent->left == NULL)) {
      Node* getSide = currentNode;
      while (getSide->parent != head) {
	getSide = getSide->parent;
      }
      if (getSide->parent->left == getSide) {
	changeColor(head->left);
      }
      else {
	changeColor(head->right);
      }
    }
  }
  fixReds(head);
  //check for two reds in a row
  
  //fix(head);
}

Node* Tree::findRotation(Node* current) {
 if (current->right != NULL) {
    Node* returnNode = findRotation(current->right);
    if (returnNode == NULL && current == head) {
      
    }
    else {
      return returnNode;
    }
 }
 if (current->left != NULL) {
    Node* returnNode = findRotation(current->left);
    if (returnNode == NULL && current == head) {
      return returnNode;
    }
 }

  int leftBlacks = 0;
  int rightBlacks = 0;
  if (current->right != NULL) {
    rightBlacks = countBlacks(current->right, 0);
  }
  if (current->left != NULL) {
    leftBlacks = countBlacks(current->left, 0);
  }
  if (leftBlacks == 0 || rightBlacks == 0) {
    return NULL;
  }
  if (rightBlacks > leftBlacks) {
    //cout << "Right side greater" << endl;
    //display(current, 0);
    
    int leftCheck = leftBlacks + 1;
    if (leftCheck == rightBlacks && current->color == 1 && current->left != NULL && current->right != NULL) {
      if (current->left->color == 0 && current->right->color == 1) {
	changeColor(current->left);
	return current;
      }
      if (current->left->color == 1 && current->right->color == 1) {
	changeColor(current->right);
	return current;
      }
    }
    if (current == head) {
      Node* returnNode = findRotation(current->right);
      return returnNode;
      
    }
    if (current->parent == head && current->color == 0) {
      changeColor(current);
      return current;
    }
    //rotate Node
    
    //get replacement Node
    Node* replace = current->right;
    while (replace->left != NULL) {
      replace = replace->left;
    }
    //remove replace node from tree
    if (replace != current->right) {
    replace->parent->left = NULL;
    }
    if (replace->right != NULL && replace != current->right) {
      replace->parent->left = replace->right;
      replace->right->parent = replace->parent;
      replace->right->color = replace->color;
      replace->right = NULL;
      
    }
    replace->parent = NULL;
    //place replace node where current is
    replace->parent = current->parent;
    if (current->parent->left == current) {
      current->parent->left = replace;
    }
    else {
      current->parent->right = replace;
    }
    current->parent = replace;
    replace->left = current;
    if (replace != current->right) {
      replace->right = current->right;
      current->right->parent = replace;
    }
    current->right = NULL;
    //move down the left side and fix the shift
    Node* moving = current;
    //CHANGE COLOR
    replace->color = current->color;
    /*if (replace->right != NULL) {
      if (replace->right->color == replace->color) {
	if (replace->color == 0) {
	  replace->right->color = 1;
	}
	else {
	  replace->right->color = 0;
	}
      }
    }
    if (replace->left != NULL) {
      if (replace->left->color == replace->color) {
	if (replace->color == 0) {
	  replace->left->color = 1;
	}
	else {
	  replace->left->color = 0;
	}
      }
    }*/
    if (replace->right != NULL) {
      if (replace->right->color == replace->color) {
	changeColor(replace->right);
      }
    }
    if (replace->left != NULL) {
      if (replace->left->color == replace->color) {
	changeColor(replace->left);
      }
    }
    while (moving->right == NULL) {
      //shift
      //make their left node their right's furthest left Node
      //move down the tree one (reset current)
      if (moving->left == NULL) {
	cout << "Switch terminated" << endl;
	break;
      }
      Node* replaceNode2 = moving->left;
      while (replaceNode2->right != NULL) {
	replaceNode2 = replaceNode2->right;
      }
      if (replaceNode2->left != NULL) {
	replaceNode2->left->parent = replaceNode2->parent;
	if (replaceNode2 == moving->left) {
	  replaceNode2->parent->left = replaceNode2->left;
	  if (replaceNode2->parent->color == 0) {
	    replaceNode2->parent->left->color = 1;
	  }
	  else {
	    replaceNode2->parent->left->color = 0;
	  }
	}
	else {
	replaceNode2->parent->right = replaceNode2->left;
	//recolor
	replaceNode2->left->color = replaceNode2->color;
	}
	replaceNode2->left = NULL;
      }
      replaceNode2->parent->right = NULL;
      replaceNode2->parent = moving->parent;
      moving->parent->left = replaceNode2;
      if (moving->left != replaceNode2) {
	moving->left->parent = replaceNode2;
	replaceNode2->left = moving->left;
      }
      moving->left = NULL;
      moving->parent = replaceNode2;
      replaceNode2->right = moving;
      //recolor
      replaceNode2->color = moving->color;
      if (replaceNode2->color == 0) {
	moving->color = 1;
      }
      else {
	moving->color = 0;
      }
      if (replaceNode2->left == NULL) {
	break;
      }
      moving = replaceNode2->left;
    }
    //cout << "Fix: " << endl;
    //display(head,0);
    return current;
  }
  else if (leftBlacks > rightBlacks) {
    //cout << "Left side greater" << endl;
    //display(current, 0);
    
    int checkRight = rightBlacks+1;
    if (checkRight == leftBlacks && current->color == 1) {
      if (current->right->color == 0 && current->left->color == 1) {
	changeColor(current->right);
	return current;
      }
      if (current->right->color == 1 && current->left->color == 1) {
	changeColor(current->left);
	return current;
      }
    }
    if (current == head) {
      Node* returnNode = findRotation(head->left);
      return returnNode;
    }
    if (current->parent == head && current->color == 0) {
      changeColor(current);
      return current;
    }
    //rotate Node
    
    //get replacement Node
    Node* replace = current->left;
    while (replace->right != NULL) {
      replace = replace->right;
    }
    //remove replace node from tree
    if (replace != current->left) {
    replace->parent->right = NULL;
    }
    if (replace->left != NULL && replace != current->left) {
      replace->parent->right = replace->left;
      replace->left->parent = replace->parent;
      replace->left->color = replace->color;
      replace->left = NULL;
      
    }
    replace->parent = NULL;
    //place replace node where current is
    replace->parent = current->parent;
    if (current->parent->left == current) {
      current->parent->left = replace;
    }
    else {
      current->parent->right = replace;
    }
    current->parent = replace;
    replace->right = current;
    if (replace != current->left) {
      replace->left = current->left;
      current->left->parent = replace;
    }
    current->left = NULL;
    //move down the left side and fix the shift
    Node* moving = current;
    //CHANGE COLOR
    replace->color = current->color;
    /*if (replace->left != NULL) {
      if (replace->left->color == replace->color) {
	if (replace->color == 0) {
	  replace->left->color = 1;
	}
	else {
	  replace->left->color = 0;
	}
      }
    }
    if (replace->right != NULL) {
      if (replace->right->color == replace->color) {
	if (replace->color == 0) {
	  replace->right->color = 1;
	}
	else {
	  replace->right->color = 0;
	}
      }
    }*/
    if (replace->left != NULL) {
      if (replace->left->color == replace->color) {
	changeColor(replace->right);
      }
    }
    if (replace->right != NULL) {
      if (replace->right->color == replace->color) {
	changeColor(replace->left);
      }
    }
    while (moving->left == NULL) {
      //shift
      //make their left node their right's furthest left Node
      //move down the tree one (reset current)
      if (moving->right == NULL) {
	//cout << "Switch terminated" << endl;
	break;
      }
      Node* replaceNode2 = moving->right;
      while (replaceNode2->left != NULL) {
	replaceNode2 = replaceNode2->left;
      }
      if (replaceNode2->right != NULL) {
	replaceNode2->right->parent = replaceNode2->parent;
	if (replaceNode2 == moving->right) {
	  replaceNode2->parent->right = replaceNode2->right;
	  if (replaceNode2->parent->color == 0) {
	    replaceNode2->parent->right->color = 1;
	  }
	  else {
	    replaceNode2->parent->right->color = 0;
	  }
	}
	else {
	replaceNode2->parent->left = replaceNode2->right;
	//recolor
	replaceNode2->right->color = replaceNode2->color;
	}
	replaceNode2->right = NULL;
      }
      replaceNode2->parent->left = NULL;
      replaceNode2->parent = moving->parent;
      moving->parent->right = replaceNode2;
      if (moving->right != replaceNode2) {
	moving->right->parent = replaceNode2;
	replaceNode2->right = moving->right;
      }
      moving->right = NULL;
      moving->parent = replaceNode2;
      replaceNode2->left = moving;
      //recolor
      replaceNode2->color = moving->color;
      if (replaceNode2->color == 0) {
	moving->color = 1;
      }
      else {
	moving->color = 0;
      }
      if (replaceNode2->right == NULL) {
	break;
      }
      moving = replaceNode2->right;
    }
    //cout << "Fix: " << endl;
    //display(head,0);
    return current;

  }
  return NULL;
}

int Tree::countBlacks(Node* root, int height) {
  if (root == NULL) {
    return 0;
  }
  int leftHeight = height;
  int rightHeight = height;
  height += root->color;
  if (root->left != NULL) {
    leftHeight = countBlacks(root->left, height);
  }
  else {
    leftHeight = height;
  }
  if (root->right != NULL) {
    rightHeight = countBlacks(root->right, height);
  }
  else {
    rightHeight = height;
  }
  if (leftHeight > rightHeight) {
    return leftHeight;
  }
  else {
    return rightHeight;
  }
}

void Tree::display(Node* printNode, int height) {
  if (printNode == NULL) {
    return;
  }
  if (printNode->right != NULL) {
    int newHeight = height+1;
    display(printNode->right, newHeight);
  }
  for (int i = 0; i < height; i++) {
    cout << "\t";
  }
  cout << printNode->number << ", ";
  if (printNode->color == 0) {
    cout << "R" << endl;
  }
  else {
    cout << "B" << endl;
  }
  if (printNode->left != NULL) {
    int newHeight = height+1;
    display(printNode->left, newHeight);
  }
  
}
//NOT PROPERLY REPLACING LEFT SIDE IF BOTTOM ROW IS BLACK
int Tree::needChange(Node* current) {
  if (current->right != NULL) {
    if (current->color == 0 && current->right->color == 0) {
      changeColor(current->right);
    }
    int check = needChange(current->right);
    if (check != 0) {
      return check;
    }
  }
  if (current->left != NULL) {
    if (current->color == 0 && current->left->color == 0) {
      changeColor(current->left);
    }
    int check = needChange(current->left);
    if (check != 0) {
      return check;
    }
  }
  if (current != head) {
    if (current->parent != head) {
    if (current->color == 1 && (current->parent->right == NULL || current->parent->left == NULL)) {
      Node* getSide = current;
	while (getSide->parent != head) {
	  getSide = getSide->parent;
	}
	if (getSide->parent->left == getSide) {
	  return 2;
	}
	else {
	  return 1;
	}
    }
    if (current->color == 1) {
      if (current->parent->parent->left == current->parent) {
	if (current->parent->parent->right != NULL) {
	  if (current->parent->parent->right->right == NULL || current->parent->parent->right->left == NULL) {
	    Node* getSide = current;
	while (getSide->parent != head) {
	  getSide = getSide->parent;
	}
	if (getSide->parent->left == getSide) {
	  return 2;
	}
	else {
	  return 1;
	}
	  }
	}
      }
    }
    if (current->parent->parent->right == current->parent) {
      if (current->parent->parent->left != NULL) {
	if (current->parent->parent->left->left == NULL || current->parent->parent->left->right == NULL) {
	    Node* getSide = current;
	while (getSide->parent != head) {
	  getSide = getSide->parent;
	}
	if (getSide->parent->left == getSide) {
	  return 2;
	}
	else {
	  return 1;
	} 
	}
      }
    }
    }
  }
  if (current != head && current->right == NULL && current->left == NULL) {
    if (current->parent->right == NULL || current->parent->left == NULL) {
      if (current->color == 1) {
	Node* getSide = current;
	while (getSide->parent != head) {
	  getSide = getSide->parent;
	}
	if (getSide->parent->left == getSide) {
	  return 2;
	}
	else {
	  return 1;
	}
      }
    }
  }
  return 0;
}

Node* Tree::getHead() {
  return head;
}

int Tree::checkEven(Node* current, Node* insert) {
  if (current->left != NULL && current->right == NULL && current->left != insert) {
    return 1;
  }
  if (current->right != NULL && current->left == NULL && current->right != insert) {
    return 1;
  }
  if (current->left != NULL && current->right != NULL) {
    if ((current->right->left != NULL && current->right->left != insert) && (current->left->right == NULL || current->left->left == NULL || current->right->right == NULL)) {
    return 1;
  }
  if ((current->right->right != NULL && current->right->right != insert)&& (current->right->left == NULL || current->left->left == NULL || current->left->right == NULL)) {
    return 1;
  }
  if ((current->left->left != NULL && current->left->left != insert)  && (current->right->right == NULL || current->right->left == NULL || current->left->right == NULL)) {
      return 1;
  }
  if ((current->left->right != NULL && current->left->right != insert) && (current->right->right == NULL || current->right->left == NULL || current->left->left == NULL)) {
    return 1;
  }
  }
  if (current->right != NULL) {
  int check = checkEven(current->right, insert);
    if (check == 1) {
      return 1;
    }
  }
  if (current->left != NULL) {
    int check = checkEven(current->left, insert);
    if (check == 1) {
      return 1;
    }
  }
  return 0;
}
void Tree::changeColor(Node* top) {
  if (top->parent->color == 1 && top->color == 0 && top->parent != head) {

  }
  else if (top->color == 0) {
    top->color = 1;
  }
  else {
    top->color = 0;
  }
  
  if (top->left != NULL) {
    changeColor(top->left);
  }
  if (top->right != NULL) {
    changeColor(top->right);
  }
}
Node* Tree::traverse(Node* current) {
  if (current->right == NULL && current->left == NULL) {
    return current;
  }
  if (current->right != NULL) {
    traverse(current->right);
  }
  if (current->left != NULL) {
    traverse(current->left);
  }
  return NULL;
}

/*void Tree::fix(Node* current) {
  //check if one side has 2x length
  if (current->left == NULL || current->right == NULL) {
    return;
  }
  if (current->left->left == NULL && current->right->right == NULL && current->right->left == NULL && current->left->right == NULL) {
    return;
  }
  int leftBlacks = 0;
  int rightBlacks = 0;
  if (current->right != NULL) {
    rightBlacks = countBlacks(current->right, 0);
  }
  if (current->left != NULL) {
    leftBlacks = countBlacks(current->left, 0);
  }
  if (leftBlacks > rightBlacks && current->right != NULL && current->left != NULL && current != head) {
    cout << "Left Greater Found" << endl;
    display(head, 0);
    //get replaceNode
    Node* replaceNode = current->left;
    while (replaceNode->right != NULL) {
      replaceNode = replaceNode->right;
    }
    if (replaceNode == current->left) {
      return;
    }
    replaceNode->parent->right = NULL;
    
    if (replaceNode->left != NULL) {
      replaceNode->parent->right = replaceNode->left;
      replaceNode->left->parent = replaceNode->parent;
      replaceNode->left = NULL;
    }
    replaceNode->parent = current->parent;
    if (current->parent->left == current) {
      current->parent->left = replaceNode;
    }
    else {
      current->parent->right = replaceNode;
    }
    replaceNode->left = current->left;
    current->left->parent = replaceNode;
    replaceNode->right = current;
    current->parent = replaceNode;
    current->left = NULL;
    if (current->right != NULL) {
      replaceNode->right = current->right;
      current->right->parent = replaceNode;
      current->right = NULL;
    }
    //recolor
    replaceNode->color = current->color;
    if (replaceNode->color == 0) {
      current->color = 1;
    }
    else {
      current->color = 0;
    }
    if (current->right != NULL) {
      Node* picked = current->right;
      if (current->color == 0) {
	picked->color = 1;
      }
      else {
	picked->color = 0;
	}
      
      while (picked->left == NULL) {
	if (picked->right == NULL) {
	  if (picked->color == 0) {
	    picked->right->color = 1;
	  }
	  else {
	    picked->right->color = 0;
	  }
	  break;
	}
	if (picked->right->right == NULL && picked->right->left == NULL) {
	  if (picked->color == 0) {
	    picked->right->color = 1;
	  }
	  else {
	    picked->right->color = 0;
	  }
	  break;
	}
	Node* replace = picked->right;
	while (replace->left != NULL) {
	  replace = replace->left;
	}
	replace->parent = picked->parent;
	picked->parent->right = replace;
	if (replace != picked->right) {
	  replace->right = picked->right;
	  picked->right->parent = replace;
	}
	replace->left = picked;
	picked->parent = replace;
	picked->left = NULL;
	picked->right = NULL;
	replace->color = picked->color;
	if (replace->color == 0) {
	  picked->color = 1;
	  if (replace->right != NULL) {
	    replace->right->color = 1;
	  }
	}
	else {
	  picked->color = 0;
	  if (replace->right != NULL) {
	    replace->right->color = 0;
	  }
	}
	if (picked->right == NULL) {
	  break;
	}
	picked = picked->right;
      }
      display(head, 0);
    }
    //balance(current);
  }
  if (rightBlacks > leftBlacks && current->left != NULL && current->right != NULL) {
    cout << "Right Greater Found" << endl;
    display(head, 0);
   //get replaceNode
    Node* replaceNode = current->right;
    while (replaceNode->left != NULL) {
      replaceNode = replaceNode->left;
    }
    if (replaceNode == current->right) {
      return;
    }
    replaceNode->parent->left = NULL;
    replaceNode->parent = current->parent;
    if (current->parent->right == current) {
      current->parent->right = replaceNode;
    }
    else {
      current->parent->left = replaceNode;
    }
    replaceNode->right = current->right;
    current->right->parent = replaceNode;
    replaceNode->left = current;
    current->parent = replaceNode;
    current->right = NULL;
    //recolor
    replaceNode->color = current->color;
    if (replaceNode->color == 0) {
      current->color = 1;
    }
    else {
      current->color = 0;
    }
    if (current->left != NULL) {
      Node* picked = current->left;
      if (current->color == 0) {
	picked->color = 1;
      }
      else {
	picked->color = 0;
      }
      while (picked->right == NULL) {
	if (picked->left == NULL) {
	  break;
	}
	Node* replace = picked->left;
	while (replace->right != NULL) {
	  replace = replace->right;
	}
	replace->parent = picked->parent;
	picked->parent->left = replace;
	if (replace != picked->left) {
	  replace->left = picked->left;
	  picked->left->parent = replace;
	}
	replace->right = picked;
	picked->parent = replace;
	picked->right = NULL;
	picked->left = NULL;
	replace->color = picked->color;
	if (replace->color == 0) {
	  picked->color = 1;
	  if (replace->left != NULL) {
	    replace->left->color = 1;
	  }
	}
	else {
	  picked->color = 0;
	  if (replace->left != NULL) {
	    replace->left->color = 0;
	  }
	}
	if (picked->left == NULL) {
	  break;
	}
	picked = picked->left;
      }
      display(head, 0);
    }
    //balance(current);
    }
  if (current->left != NULL) {
    if (current->left->left != NULL && current->left->right != NULL) {
    fix(current->left);
    }
  }
  if (current->right != NULL) {
    if (current->right->right != NULL && current->right->left != NULL) {
      fix(current->right);
    }
  }
  }*/
void Tree::fixReds(Node* current) {
  if (current->parent != NULL && current != NULL) {
    if (current->parent->color == 0 && current->color == 0) {
      changeColor(current);
    }
    if (current->parent != head) {
      if (current->parent->color == 1 && current->color == 1) {
	changeColor(current);
      }
    }
  }
  if (current->right != NULL) {
    fixReds(current->right);
  }
  if (current->left != NULL) {
    fixReds(current->left);
  }
}
