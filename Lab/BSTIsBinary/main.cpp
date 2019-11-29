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
    int search(int);
    void insert(int);
    bool remove(int);
    void display(){inorder(root);cout<<endl;}
};

int main(){
    int testCases;
    cin>>testCases;

    while(testCases){
        int size;
        cin>>size;
        bst b;

        while(size){
            int x;
            cin>>x;
            b.insert(x);
            size--;
        }

        int searchItem;
        cin>>searchItem;

        int comparisons = b.search(searchItem);
        string status = comparisons > 0 ? "FOUND" : "!FOUND";
        comparisons = comparisons > 0 ? comparisons : comparisons * -1;

        cout << comparisons << " " << status << endl; 
        testCases--;
    }
    return 0;
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

int bst::search(int x) {
    int count = 0;

    bstnode *curr = root;

    while(curr!=NULL){
        count++;

        if(x == curr->item) {
            return count;
        }
        else if(x < curr->item)
            curr = curr->left;
        else
            curr = curr->right;
    }
    return count * -1;
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

int bst::minimum(bstnode* r){
    if(r==NULL)
        throw -1;
    else{
        bstnode *curr = r;
        while(curr->left!=NULL) {
            curr = curr->left;
        }
        return curr->item;
    }
}