#include <iostream>

using namespace std;

class Heap {
private:
    int _size;
    int _arr[100];
public:
    Heap();
    void insert(int);
    int first();
};

int main() {
    
    int testCases;
    cin >> testCases;

    while(testCases > 0) {
        int size;
        cin >> size;

        Heap h;

        while(size > 0) {
            int element;
            cin >> element;
            
            h.insert(element);
            
            cout << h.first() << endl;

            size--;
        }

        testCases--;
    }

    return 0;
}

Heap::Heap() {
    _size = 1;
}

void Heap::insert(int element) {
    if(_size == 0) {
        _arr[_size] = element;
    }
    else {
        _arr[_size] = element;
        int x = _size;

        while(x > 1) {
            if(_arr[x] < _arr[x/2]) {
                int temp = _arr[x];
                _arr[x] = _arr[x/2];
                _arr[x/2] = temp;
                x = x/2;
            } else
                break;
        }
        
    }

    _size++;
}

int Heap::first() {
    return _arr[1];
}