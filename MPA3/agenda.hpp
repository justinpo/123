#include <stack>
#include <queue>
#include <typeinfo>
#include "cell.hpp"

template <class T>
class Agenda{
private:
    T *_adt;
    int _type; //1 for stack, 2 for queue
public:
    Agenda();
    ~Agenda();
    void add(Cell);
    bool remove();
    bool isEmpty();
    int getSize();
    Cell peek();
};

template <class T>
Agenda<T>::Agenda(){
    _adt = new T();
    string t1 = typeid(*_adt).name();
    string t2 = typeid(stack<Cell>).name();
    string t3 = typeid(queue<Cell>).name();
    if(t1.compare(t2)==0)
        _type = 1;
    else if(t1.compare(t3)==0)
        _type = 2;
}

template <class T>
Agenda<T>::~Agenda() {
    delete _adt;
}

template <class T>
void Agenda<T>::add(Cell cell) {
    _adt->push(cell);
}

template <class T>
bool Agenda<T>::remove() {
    if(isEmpty())
        return false;
    else {
        _adt->pop();
        return true;
    }
}

template <class T>
bool Agenda<T>::isEmpty() {
    return _adt->empty();
}

template <class T>
int Agenda<T>::getSize() {
    return _adt->size();
}

template <class T>
Cell Agenda<T>::peek() {
    return _type == 1 ? ((stack<Cell>*)_adt)->top() : ((queue<Cell>*)_adt)->front();
}