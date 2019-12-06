#include "node.hpp"

using namespace std;

class Tree {
private:
  Node *_root;

public:
  Tree();
  Node* root();
  void insert(Node*, Node*);
  void remove(string, Node*);
  void filteredRemove(string, Node*);
};

Tree::Tree() {
  _root = new Node("root", directory);
}

Node* Tree::root() {
  return _root;
}

void Tree::insert(Node *n, Node *parent) {
  n->_parent = parent;

  parent->_children.push_back(n);
}

void Tree::remove(string name, Node *parent) {
  Node *curr = parent->getNode(name);

  if(curr != NULL) {
    parent->_children.remove(curr);
  }
}

void Tree::filteredRemove(string filter, Node *parent) {
  for(auto i : parent->_children) {

    if(filter[0] == '*' && filter[filter.length() - 1] == '*') {
			string tempFilter = filter.substr(1, filter.length() - 2);
			string filename = i->_item.name();
			if(filename.find(tempFilter) != string::npos) {
        if(filename.find(tempFilter) != 0)
				  parent->_children.remove(i);
			}
		} else if(filter[0] == '*') {
			string filename = i->_item.name();
			string tempFilter = filter.substr(1, filter.length() - 1);
			if(filename.find(tempFilter) != string::npos) {
				if(filename.substr(filename.find(tempFilter), tempFilter.length()) == tempFilter) {
					parent->_children.remove(i);
				}
			}
		} else if(filter[filter.length() - 1] == '*') {
			string filename = i->_item.name();
			string tempFilter = filter.substr(0, filter.length() - 1);
			if(filename.find(tempFilter) != string::npos) {
				if(filename.substr(0, tempFilter.length()) == tempFilter) {
					parent->_children.remove(i);
				}
			}
		}
    
  }
}