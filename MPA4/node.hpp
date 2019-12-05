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
	// Node(string, Node*);
	// Node(const Node&);
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

// functions nga wa ni gana pero basin mu gana

// Node::Node(string name, Node *copy) {
// 	_item = File(name, copy->_item.type());
// 	_parent = copy->_parent;
// 	_next = copy->_next;
// 	_prev = copy->_prev;
// 	_nextLevel = copy->_nextLevel;
// 	_item.writeContent(copy->_item.content());
// }

// Node::Node(const Node &n){
// 	_item = n._item;
// 	_parent = n._parent;
// 	_next = n._next;
// 	_prev = n._prev;
// 	_nextLevel = n._nextLevel;
// }

void Node::display(ofstream& outputFile) {
	Node *curr = _nextLevel;

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