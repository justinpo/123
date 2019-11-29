#include <iostream>
#include <cmath>

using namespace std;

class bstnode{
public:
	int item;
	bstnode *left, *right, *parent;
	bstnode(int x){
		item = x;
		left = right = parent = NULL;
	}
	bstnode(){
		left = right = parent = NULL;
	}
};

class bst{
private:
	bstnode *root;
	void preorder(bstnode*);
    void inorder(bstnode*);
	int minimum(bstnode*);
public:
	bst(){root = NULL;}
    ~bst();
	bool search(int);
	void insert(int);
	bool remove(int);
	void display(){inorder(root);cout<<endl;}

};

int main(){
	int n;
    cin>>n;
    while(n){
        int m;
        cin>>m;
        bst b;
        while(m){
            int x;
            cin>>x;
            b.insert(x);
            m--;
        }
        int s;
        cin>>s;
        bool f = b.remove(s);
        if(f)
            cout<<"FOUND"<<endl;
        else
            cout<<"!FOUND"<<endl;
        n--;
    }
	return 0;
}

bst::~bst(){
    while(root!=NULL){      
       remove(root->item);        
    }        
}

void bst::preorder(bstnode* r){
	if(r!=NULL){
		cout<<r->item<<" ";
		preorder(r->left);
		preorder(r->right);
	}
}

void bst::inorder(bstnode* r){
	if(r!=NULL){
		inorder(r->left);
        cout<<r->item<<" ";
		inorder(r->right);
	}
}

bool bst::search(int x){
	bstnode *curr = root;

	while(curr!=NULL){
		if(x == curr->item)
			return true;
		else
		if(x < curr->item)
			curr = curr->left;
		else
			curr = curr->right;
	}
	return false;
}

void bst::insert(int x){
	bstnode *n = new bstnode(x);
	if(root == NULL)
		root = n;
	else{
		bstnode *curr = root, *prev;
		while(curr!=NULL){
			prev = curr;
			if(x < curr->item)
				curr = curr->left;
			else
				curr = curr->right;
		}
		if(x < prev->item)
			prev->left = n;
		else
			prev->right = n;
		n->parent = prev;
	}
}

bool bst::remove(int x){
	bstnode *curr = root;
	int child=0;
	while(curr!=NULL){
		if(x == curr->item)
			break;
		else
		if(x < curr->item){
			curr = curr->left;
			child = -1;
		}
		else{
			curr = curr->right;
			child = 1;
		}
	}
	if(curr==NULL)
		return false;
	else{
		bstnode *del;
        bstnode *parent = curr->parent;
		if(curr->left == NULL && curr->right==NULL){
            del = curr;
			del->parent = NULL;
            if(child==1)
                parent->right = NULL;
            else
            if(child==-1)
                parent->left = NULL;
            else
            if(child==0)
                root = NULL;
			delete del;             
            
		}
		else{            
			del = curr;
            if(curr->right == NULL){
				bstnode *left = curr->left;				
				left->parent = parent;
				if(curr==root)
					root = left;
				else{
					if(child==1)
						parent->right = left;
					else
					if(child==-1)
						parent->left = left;
				}
                delete del;
			}
			else
			if(curr->left == NULL){
				bstnode *right = curr->right;				
				right->parent = parent;
				if(curr==root)
					root = right;
				else{
					if(child==1)
						parent->right = right;
					else
					if(child==-1)
						parent->left = right;
				}
                delete del;
			}
			else{
				bstnode *rightsubtree = curr->right;
                int min = minimum (rightsubtree);                
				remove(min);                
				curr->item = min;
			}
		}
        return true;
	}
}

int bst::minimum(bstnode* r){
	if(r==NULL)
		throw -1;
	else{
		bstnode *curr = r;
		while(curr->left!=NULL)
			curr = curr->left;
		return curr->item;
	}
}