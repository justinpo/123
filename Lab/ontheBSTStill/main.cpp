#include <iostream>
#include <cmath>
#include <vector>

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
    vector<int> v;
    void preorder(bstnode*);
    void inorder(bstnode*);
    int getMinimum(bstnode*);
    int getMaximum(bstnode*);
    void makeVector(bstnode*, int);

public:
    bst(){root = NULL;}
    ~bst();
    bool search(int);
    bstnode* getNode(int);
    void insert(int);
    bool remove(int);
    void display(){inorder(root);cout<<endl;}
    bool isancestor(int, int);
    bool isdescendant(int, int);
    int minimum(bstnode*);
    int maximum(bstnode*);
    void successor(bstnode*, int);
    bstnode* treeRoot();
};

int main(){
    int testCases;
    cin>>testCases;
    
    while(testCases){
        int size;
        cin>>size;
        bst b;

        while(size){
            int node;
            cin>>node;
            b.insert(node);
            size--;
        }

        bstnode* root = b.treeRoot();

        int toRemove;
        cin>>toRemove;
        b.remove(toRemove);
        
        b.display();
        cout << b.minimum(root) << endl;
        cout << b.maximum(root) << endl;

        int x, y;
        cin >> x >> y;
        string answer = b.isancestor(x, y) ? "YES" : "NO";
        cout << answer << endl;

        cin >> x >> y;
        answer = b.isdescendant(x, y) ? "YES" : "NO";
        cout << answer << endl;

        cin >> x;
        b.successor(root, x);

        testCases--;
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

bstnode* bst::getNode(int x){
    bstnode *curr = root;

    while(curr!=NULL){
        if(x == curr->item)
            return curr;
        else
        if(x < curr->item)
            curr = curr->left;
        else
            curr = curr->right;
    }

    return curr;
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

int bst::getMinimum(bstnode* r){
    if(r==NULL)
        throw -1;
    else{
        bstnode *curr = r;
        while(curr->left!=NULL)
            curr = curr->left;
        return curr->item;
    }
}

int bst::getMaximum(bstnode* r){
    if(r==NULL)
        throw -1;
    else{
        bstnode *curr = r;
        while(curr->right!=NULL)
            curr = curr->right;
        return curr->item;
    }
}

int bst::minimum(bstnode* r){
    return getMinimum(r);
}

int bst::maximum(bstnode* r){
    return getMaximum(r);
}

void bst::makeVector(bstnode* r, int x) {
    if(r!=NULL){
        makeVector(r->left, x);
        v.push_back(r->item);
        makeVector(r->right, x);
    }
}

void bst::successor(bstnode* r, int x) {
    makeVector(r, x);

    for(int i = 0; i < v.size(); i++) {
        if(v.at(i) == x) {
            if(v.back() != x) {
                cout << v.at(i+1) << endl;
            } else {
                cout << "NONE" << endl;
            }
        }
    }
}

bool bst::isancestor(int x, int y) {
    if(!search(x) || !search(y))
        return false;

    bstnode* curr = getNode(y);
    curr = curr->parent;

    while(curr != NULL) {
        if(curr->item == x)
            return true;
        else
            curr = curr->parent;
    }

    return false;
}

bool bst::isdescendant(int x, int y) {
    if(!search(x) || !search(y))
        return false;

    bstnode* curr = getNode(x);
    curr = curr->parent;

    while(curr != NULL) {
        if(curr->item == y)
            return true;
        else
            curr = curr->parent;
    }

    return false;
}

bstnode* bst::treeRoot() {
    return root;
}