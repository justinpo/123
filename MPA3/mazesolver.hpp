#include <fstream>
#include "maze.hpp"

template <class T>
class Mazesolver {
private:
    Agenda<T> *_agenda;
    Maze *_maze, *_solution;
    stack<Cell> *_path;

public:
    Mazesolver(Maze*);
    ~Mazesolver();
    void solve();
    void setSolution();
    void writeSolution(ofstream&);
};

template <class T>
Mazesolver<T>::Mazesolver(Maze *maze) {
    _agenda = new Agenda<T>();
    _maze = maze;
    _path = new stack<Cell>();
}

template <class T>
Mazesolver<T>::~Mazesolver() {
    delete _agenda;
    delete _path;
}

template <class T>
void Mazesolver<T>::setSolution() {
    _solution = new Maze(_maze);

	if(!_path->empty()) {
        _path->pop();
    	while(!_path->empty()){
	        if(_path->size() == 1){
	            break;
	        }
	        Cell curr = _path->top();
            curr.visit();
            _solution->add(curr, curr._row, curr._col);
	        _path->pop();
    	}
	}
}

template <class T>
void Mazesolver<T>::solve() {
    bool left, top, right, bottom, pathFound = false;
    Cell curr;

    Maze *temp  = new Maze(_maze);
    int x = temp->start()._row;
    int y = temp->start()._col;
    _path->push(temp->_cells[x][y]);

    while(!pathFound && !_path->empty()) {

        curr = _path->top();
        x = curr._row;
        y = curr._col;
        
        if(curr._type == destination)
            pathFound = true;

        else {
            temp->_cells[x][y]._visited = true;

            left = y > 0 && temp->_cells[x][y-1]._type != wall && temp->_cells[x][y-1]._visited == false;
            top = x > 0 && temp->_cells[x-1][y]._type != wall && temp->_cells[x-1][y]._visited == false;
            right = (y < temp->_columns - 1) && temp->_cells[x][y+1]._type != wall && temp->_cells[x][y+1]._visited == false;
            bottom = (x < temp->_rows - 1) && temp->_cells[x+1][y]._type != wall && temp->_cells[x+1][y]._visited == false;

            if(left)
                _agenda->add(temp->_cells[x][y-1]);
            if(top)
                _agenda->add(temp->_cells[x-1][y]);
            if(right)
                _agenda->add(temp->_cells[x][y+1]);
            if(bottom)
                _agenda->add(temp->_cells[x+1][y]);

            if(_agenda->isEmpty())
                _path->pop();

            else {
                _path->push(_agenda->peek());

                while(!_agenda->isEmpty()){
                    _agenda->remove();
                }
            }
        }
    }

    setSolution();
}

template <class T>
void Mazesolver<T>::writeSolution(ofstream& outputFile){
    outputFile << _solution->str();
    outputFile << endl;
}