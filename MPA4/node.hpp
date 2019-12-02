#include "filedescriptor.hpp"
#include <list>
#include <iostream>

using namespace std;

class Node {
public:
	FileDescriptor _item;
  Node* _parent;
	Node* _next;
	Node* _prev;
	list<Node*> _children;

	Node();
	Node(string, fileType);
  void display(Node*);
};

Node::Node() {
	_parent = _next = _prev = NULL;
}

Node::Node(string name, fileType type) {
	_item = FileDescriptor(name, type, Date(2019, 12, 4));
	_parent = _next = _prev = NULL;
}

void Node::display(Node* curr) {
	if(curr != NULL) {
		display(curr->_prev);
		cout << _item.name() << endl;
		display(curr->_next);
	}
}