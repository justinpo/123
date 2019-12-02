#include "node.hpp"

using namespace std;

class Tree {
private:
  Node *_root;

public:
  void insert(string, fileType);
  void remove(string);
  FileDescriptor search(string);
};

void Tree::insert(string name, fileType type) {
  Node* n = new Node(name, type);
}