#ifndef NODE_H
#define NODE_H
#include <iostream>

using namespace std;

//0 = red, 1 = black

struct Node {
  Node* left = NULL;
  Node* right = NULL;
  Node* parent = NULL;
  int number = 0;
  int color = 0;
};
#endif
