#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

class Hashtable {
private:
    int _size;
    int _max;
    int _arr[512];

public:
    Hashtable();
    int hash(int);
    int find(int);
    int insert(int);
};

int main() {
    int testCases;

    cin >> testCases;

    while(testCases > 0) {
        int size;
        cin >> size;

        Hashtable h;

        while(size > 0) {
            int element;
            cin >> element;
            cout << h.insert(element) << " ";
            size--;
        }

        cout << endl;

        int searchItem;
        cin >> searchItem;

        cout << h.find(searchItem) << endl;

        testCases--;
    }

    return 0;
}

Hashtable::Hashtable(){
    int inf = std::numeric_limits<int>::infinity();
    _size = 0;
    _max = 512;
    for(int i=0; i<_max; i++)
        _arr[i] = inf;
}

int Hashtable::hash(int x) {
    int d = 9;
    int w = 16;
    int z = 60147;
    
    return (((z*x)%int(pow(2,w)))/pow(2,(w-d)));
}

int Hashtable::insert(int x){
    int inf = std::numeric_limits<int>::infinity();
    int i = hash(x);
    int collisions = 0;

    while(_arr[i] != inf) {
        i = (i+1)%_max;
        collisions++;
    }

    _arr[i] = x;
    _size++;

    return collisions;
}

int Hashtable::find(int x){
    int inf = std::numeric_limits<int>::infinity();
    int i = hash(x);
    int collisions = 0;

    while(_arr[i] != inf) {
        if(_arr[i] == x)
            break;
        i = (i+1)%_max;
        collisions++;
    }

    return collisions;
}