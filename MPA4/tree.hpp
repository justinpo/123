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