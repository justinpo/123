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
  Node* getNode(string);
};

Tree::Tree() {
  _root = new Node("root", directory);
}

Node* Tree::root() {
  return _root;
}

void Tree::insert(Node *n, Node *parent) {
  n->_parent = parent;

  if(parent->_nextLevel == NULL) {
    parent->_nextLevel = n;
  } else {
    Node *curr = parent->_nextLevel;
    while(curr->_next != NULL) {
      curr = curr->_next;
    }
    curr->_next = n;
    n->_prev = curr;
  }
}

Node* Tree::getNode(string name) {
  Node *curr = _root->_nextLevel;
  stack<Node*> s;
  s.push(curr);

  if(curr != NULL) {
    while(!s.empty()) {
      curr = s.top();
      string currName = curr->_item.name();

      if(currName == name)
        return curr;

      s.pop();

      if(curr->_nextLevel)
        s.push(curr->_nextLevel);
      if(curr->_next)
        s.push(curr->_next);
    }
  }

  return NULL;
}

void Tree::remove(string name, Node *parent) {
  Node *curr = parent->getNode(name);

  if(curr != NULL) {
    Node *parent = curr->_parent;
    if(parent->_nextLevel == curr) {
      parent->_nextLevel = curr->_next;
    }
    curr->_prev->_next = curr->_next;
    curr->_next->_prev = curr->_prev;
    curr->_parent = NULL;
  }

  if(curr->_nextLevel != NULL) {
    Node *nextLevel = curr->_nextLevel;

    Node *current = curr;
    Node *next = nextLevel->_next;
    
    while(curr != NULL) {
      next = curr->_next;
      delete curr;
      curr = next;
    }
  }

  delete curr;
}