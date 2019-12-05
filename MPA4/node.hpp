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
	list<Node*> _children;

	Node();
	Node(string, fileType);
  void display(ofstream&);
	Node* getNode(string);
};

Node::Node() {
	_parent = NULL;
}

Node::Node(string name, fileType type) {
	_item = File(name, type);
	_parent = NULL;
}

void Node::display(ofstream& outputFile) {
	for(auto i : _children) {
		outputFile << i->_item.name() << endl;
	}
}

Node* Node::getNode(string name) {
	bool found = false;
	Node *curr;

	for(auto i : _children) {
		curr = i;
		string currName = curr->_item.name();
		if(currName == name) {
			found = true;
			break;
		}

	}
  return found ? curr : NULL;
}