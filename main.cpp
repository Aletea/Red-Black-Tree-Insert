#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include "Tree.h"

using namespace std;

int main() {
  bool stillGoing = true;
  Tree* RB = new Tree();
  while (stillGoing == true) {
    //ask read, add, print, or quit
    cout << "Would you like to read, add, delete, print, or quit?" << endl;
    char input[20];
    cin.get(input,20);
    cin.get();
    while (strcmp(input, "read") != 0 && strcmp(input, "add") != 0 && strcmp(input, "print") != 0 && strcmp(input, "quit") != 0 && strcmp(input, "delete") != 0) {
      cout << "Improper input. Please type 'read', 'add', 'print', or 'quit'" << endl;
      cin.get(input,20);
      cin.get();
    }
    if (strcmp(input, "read") == 0) {
      //get file path
      cout << "Enter file path." << endl;
      char newFilePath[300];
      cin.get(newFilePath,300);
      cin.get();
      //get directory
      ifstream textFile;
      textFile.open(newFilePath);
      while (!textFile) {
	cout << "File Destination Not Found. Please Re-enter" << endl;
	cin.get(newFilePath,300);
	cin.get();
	textFile.open(newFilePath);
      }
      //get file length
      textFile.seekg(0,textFile.end);
      int length = textFile.tellg();
      textFile.seekg(0,textFile.beg);
      //run through new file and add to int array list
      char charArray[300];
      for (int i = 0; i<length; i++) {
	charArray[i] = textFile.get();
      }
      //convert characters to numbers and add to list
      for (int i = 0; i < length;i++) {
	char number[10];
	int count = 0;
	while (isdigit(charArray[i]) && i < length) {
	  number[count] = charArray[i];
	  i++;
	  count++;
        }
	number[count] = '\0';
	int newNum = atoi(number);
	Node* newNode = new Node();
	newNode->number = newNum;
	RB->insert(newNode);
	if (!isdigit(charArray[i+1])) {
	  i++;
	}
      }
      
    }
    //make new node and insert
    else if (strcmp(input, "add") == 0) {
      cout << "Enter number you are going to add." << endl;
      int num;
      cin >> num;
      cin.ignore();
      Node* newNode = new Node();
      newNode->number = num;
      RB->insert(newNode);
    }
    else if (strcmp(input, "delete") == 0) {
      cout << "Enter number you are going to delete." << endl;
      int num;
      cin >> num;
      cin.ignore();
      RB->deleteNode(num);
    }
    else if (strcmp(input, "print") == 0) {
      if (RB->getHead() == NULL) {
	cout << "No tree to print" << endl;
      }
      else {
	RB->display(RB->getHead(), 1);
      }
    }
    else {
      stillGoing = false;
    }
  }

  return 0;
}
