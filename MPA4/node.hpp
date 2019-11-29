
#include <list>

using namespace std;

class Node {
public:
  Node* parent;
	Node* next;
	Node* prev;
	Node* nextLevel;
	list<Node*> children;
}