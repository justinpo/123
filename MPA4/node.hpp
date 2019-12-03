#include "file.hpp"
#include <list>
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

class Node {
public:
	File _item;
  Node* _parent;
	Node* _next;
	Node* _prev;
	Node* _nextLevel;

	Node();
	Node(string, fileType);
  void display(ofstream&);
	Node* getNode(string);
};

Node::Node() {
	_parent = _next = _prev = NULL;
}

Node::Node(string name, fileType type) {
	_item = File(name, type);
	_parent = _next = _prev = NULL;
}

void Node::display(ofstream& outputFile) {
	Node *curr = _nextLevel;
	stack<string> s;

	while(curr != NULL) {
		outputFile << curr->_item.name() << endl;
		curr = curr->_next;
	}
}

Node* Node::getNode(string name) {
	Node *curr = _nextLevel;
	bool found = false;

    while(curr != NULL) {
      string currName = curr->_item.name();

      if(currName == name)
        break;

      curr = curr->_next;
    }

  return curr;
}