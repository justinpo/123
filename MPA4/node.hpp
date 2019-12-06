#include "file.hpp"
#include <list>
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>

using namespace std;

class Node {
public:
	File _item;
  Node* _parent;
	list<Node*> _children;

	Node();
	Node(string, fileType);
  void display(ofstream&);
	void filteredDisplay(ofstream&, string);
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

void Node::filteredDisplay(ofstream& outputFile, string filter) {
	for(auto i : _children) {
		if(filter[0] == '*' && filter[filter.length() - 1] == '*') {
			string tempFilter = filter.substr(1, filter.length() - 2);
			string filename = i->_item.name();
			if(filename.find(tempFilter) != string::npos) {
				if(filename.find(tempFilter) != 0)
					outputFile << filename << endl;
			}
		} else if(filter[0] == '*') {
			string filename = i->_item.name();
			string tempFilter = filter.substr(1, filter.length() - 1);
			if(filename.find(tempFilter) != string::npos) {
				if(filename.substr(filename.find(tempFilter), tempFilter.length()) == tempFilter) {
					outputFile << filename << endl;
				}
			}
		} else if(filter[filter.length() - 1] == '*') {
			string filename = i->_item.name();
			string tempFilter = filter.substr(0, filter.length() - 1);
			if(filename.find(tempFilter) != string::npos) {
				if(filename.substr(0, tempFilter.length()) == tempFilter) {
					outputFile << filename << endl;
				}
			}
		}
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