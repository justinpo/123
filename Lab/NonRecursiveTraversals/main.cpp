#include <iostream>
#include <cmath>
#include <stack>
#include <queue>

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
    void levelorder(bstnode*);
    void inorder(bstnode*);
    int minimum(bstnode*);
public:
    bst(){root = NULL;}
    int search(int);
    void insert(int);
    bool remove(int);
    void displayOne(){preorder(root);}
    void displayTwo(){levelorder(root);}
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

        b.displayOne();
        b.displayTwo();

        testCases--;
    }
    return 0;
}

void bst::preorder(bstnode* r){
    bstnode* curr = r;
    stack<bstnode*> s;
    s.push(curr);

    if(r != NULL) {
        while(!s.empty()) {
            curr = s.top();
            cout << curr->item << " ";
            s.pop();
            if(curr->right)
                s.push(curr->right);
            if(curr->left)
                s.push(curr->left);
        }

        cout<<endl;
    }
}

void bst::levelorder(bstnode* r){
    bstnode* curr = r;
    queue<bstnode*> s;
    s.push(curr);

    if(r != NULL) {
        while(!s.empty()) {
            curr = s.front();
            cout << curr->item << " ";
            s.pop();
            if(curr->left)
                s.push(curr->left);
            if(curr->right)
                s.push(curr->right);
        }

        cout<<endl;
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