#include <iostream>
#include <cmath>

using namespace std;

class avlnode{
public:
	int item;
	int height;
	int balance;
	int child;
	avlnode *left, *right, *parent;
	avlnode(int x){
		item = x;
		height = balance = 0;
		left = right = parent = NULL;
	}
	avlnode(){
		height = balance = child = 0;
		left = right = parent = NULL;
	}
};

class avltree{
private:
	avlnode *root;
	int height(avlnode*);
	void leftrotate(avlnode*);
	void rightrotate(avlnode*);
	void preorder(avlnode*);
public:
	avltree(){root = NULL;}
	int search(int);
	void insert(int);
	void display(){preorder(root);cout<<endl;}

};

int main(){
	
	return 0;
}

void avltree::preorder(avlnode* r){
	if(r!=NULL){
		cout<<r->item<<" ";
		preorder(r->left);
		preorder(r->right);
	}
}

int avltree::height(avlnode* n){
	if(n==NULL)
		return -1;
	else
		return n->height;
}

int avltree::search(int x){
	int count = 0;
	avlnode *curr = root;

	while(curr!=NULL){
		if(x == curr->item)
			return count+1;
		else
		if(x < curr->item){
			curr = curr->left;
			count++;
		}
		else{
			curr = curr->right;
			count++;
		}
	}
	return count*-1;
}

void avltree::insert(int x){
	avlnode *n = new avlnode(x);
	if(root == NULL)
		root = n;
	else{
		//start of bst insert
		avlnode *curr = root, *prev;
		while(curr!=NULL){
			prev = curr;
			if(x < curr->item){
				curr = curr->left;
				n->child = -1;
			}
			else{
				curr = curr->right;
				n->child = 1;
			}
		}
		if(x < prev->item)
			prev->left = n;
		else
			prev->right = n;
		n->parent = prev;
		//end of bst insert
		
		//start of update and check on violations
		curr = prev;
		do{
			int rh = height(curr->right);
			int lh = height(curr->left);
			curr->height = 1+max(lh,rh);
			if(lh > rh)
				curr->balance = -1;
			else
			if(rh > lh)
				curr->balance = 1;
			else
				curr->balance = 0;
			int dh = abs(lh-rh);
            
			if(dh>1){
                //cout<<prev->item<<" "<<curr->item<<endl;
				if(prev->balance == 1 && curr->balance == 1)
					leftrotate(curr);
				else
				if(prev->balance == -1 && curr->balance == -1)
					rightrotate(curr);
				else
				if(prev->balance == -1 && curr->balance == 1){
					rightrotate(prev);
					leftrotate(curr);
				}
				else
				if(prev->balance == 1 && curr->balance == -1){
					leftrotate(prev);
					rightrotate(curr);
				}
			}
			prev = curr;
			curr = curr->parent;
			

		}while(curr!=NULL);
		//end of update and check on violations
	}
}

void avltree::leftrotate(avlnode* n){
	//check whether there are redundant or unnecessary steps
	avlnode* p = n->parent;
	avlnode* r = n->right;
	avlnode* l = r->left;
	r->left = n;
	n->parent = r;
	r->parent = p;
	n->right = l;
	n->height = 1+max(height(n->left),height(n->right));
	r->height = 1+max(height(r->left),height(r->right));
	if(l!=NULL){
		l->parent = n;
		l->child = 1;
	}
	if(p!=NULL){
		if(n->child==1)
			p->right = r;
		else
		if(n->child==-1)
			p->left = r;
	}
	else
		root = r;
}
void avltree::rightrotate(avlnode* n){
	//check whether there are redundant or unnecessary steps
	avlnode* p = n->parent;
	avlnode* l = n->left;
	avlnode* r = l->right;
	l->right = n;
	n->parent = l;
	l->parent = p;
	n->left = r;
	n->height = 1+max(height(n->left),height(n->right));
	l->height = 1+max(height(l->left),height(l->right));
	if(r!=NULL){
		r->parent = n;
		r->child = 1;
	}
	if(p!=NULL){
		if(n->child==1)
			p->right = l;
		else
		if(n->child==-1)
			p->left = l;
	}
	else
		root = l;
}
