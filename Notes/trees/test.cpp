#include <iostream>
#include <stack>
#include <queue>

using namespace std;

template <class T>
class bstnode {
public:
  T item;
  bstnode<T> *right, *left, *parent;
  bstnode(T x) {
    item = x;
    right = left = parent = NULL;
  }
  bstnode() {
    right = left = parent = NULL;
  }
};

template <class T>
class bst {
private:
  bstnode<T> *root;
  void preorder(bstnode<T>*);
	void inorder(bstnode<T>*);
	void levelorder(bstnode<T>*);
	T minimum(bstnode<T>*); 
public:
  bst(){root = NULL;}
	bool search(T);
	void insert(T);
	void display(){inorder(root);cout<<endl;}
};

int main() {

}

template <class T>
void preorder(bstnode<T> *root) {
  if(root != NULL) {
    cout << root->item << " ";
    preorder(root->left);
    preorder(root->right);
  }
}

template <class T>
void inorder(bstnode<T> *root) {
  if(root != NULL) {
    inorder(root->left);
    cout << root->item << " ";
    inorder(root->right);
  }
}

template <class T>
void levelorder(bstnode<T> *root) {
  bstnode<T> *curr = root;
  queue<bstnode<T>*> q;
  q.push(curr);

  if(root != NULL) {
    while(!q.empty()) {
      curr = q.front();
      cout << curr->item << " ";
      q.pop();
      if(curr->left != NULL) {
        q.push(curr->left);
      }
      if(curr->right != NULL) {
        q.push(curr->right);
      }
    }
  }
}

template <class T>
T bst<T>::minimum(bstnode<T> *root) {
  bstnode<T> *curr = root;
  while(curr->left != NULL) {
    curr = curr->left;
  }

  return curr->item;
}

template <class T>
bool bst<T>::search(T x) {
  bstnode<T> curr = root;
  if(curr->item == x) {
    return true;
  } else {
    while(curr != NULL) {
      if(curr->item == x) {
        return true;
      }

      if(x < curr->item) {
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }
    return false;
  }
}

template <class T>
void bst<T>::insert(T x) {
  bstnode<T> *n = new bstnode<T>(x);
  if(root == NULL) {
    root = n;
  }
  else {
    bstnode<T> *curr = root, *prev;
    while(curr != NULL) {
      prev = curr;
      if(x < curr->left) {
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }
    if(x < prev->item) {
      prev->left = n;
    } else {
      prev->right = n;
    }
    n->parent = prev;
  }
}