#include <fstream>
#include "maze.hpp"

template <class T>
class Mazesolver {
private:
    Agenda<T> *_agenda;
    Maze *_maze;
    Agenda<stack<Cell>> *_path;

public:
    Mazesolver();
    Mazesolver(Maze*);
    ~Mazesolver();
    void solve();
    void writeSolution(ofstream&);
};

template <class T>
Mazesolver<T>::Mazesolver(Maze *maze) {
    _agenda = new Agenda<T>();
    _maze = maze;
}

template <class T>
Mazesolver<T>::~Mazesolver() {
    delete _agenda;
    delete _path;
}

template <class T>
void Mazesolver<T>::solve() {
    bool left, top, right, bottom, pathFound = false;
    Cell curr;

    // cout << 1 << endl;

    Maze *temp  = new Maze(_maze);
    int x = temp->origin()._row;
    int y = temp->origin()._col;
    _path = new Agenda<stack<Cell>>();
    _path->add(temp->_cells[x][y]);

    // cout << 2 << endl;

    while(!_path->isEmpty()) {

        // cout << 3 << endl;

        curr = _path->peek();
        x = curr._row;
        y = curr._col;
        
        if(curr._type == destination) {
            pathFound = true;
            break;
        }
        else {
            temp->_cells[x][y]._visited = true;

            left = y > 0 && temp->_cells[x][y-1]._type != wall && temp->_cells[x][y-1]._visited == false;
            top = x > 0 && temp->_cells[x-1][y]._type != wall && temp->_cells[x-1][y]._visited == false;
            right = (y < temp->_columns - 1) && temp->_cells[x][y+1]._type != wall && temp->_cells[x][y+1]._visited == false;
            bottom = (x < temp->_rows - 1) && temp->_cells[x+1][y]._type != wall && temp->_cells[x+1][y]._visited == false;

            if(left) {
                // cout << "left" << endl;
                _agenda->add(temp->_cells[x][y-1]);
            }
            if(top) {
                // cout << "top" << endl;
                _agenda->add(temp->_cells[x-1][y]);
            }
            if(right) {
                // cout << "right" << endl;
                _agenda->add(temp->_cells[x][y+1]);
            }
            if(bottom) {
                // cout << "bottom" << endl;
                _agenda->add(temp->_cells[x+1][y]);
            }

            if(_agenda->isEmpty()) {
                _path->remove();
            } else {
                _path->add(_agenda->peek());

                while(!_agenda->isEmpty()){
                    _agenda->remove();
                }
            }

            // cout << 4 << endl;
        }
    }

    // cout << 5 << endl;
}

template <class T>
void Mazesolver<T>::writeSolution(ofstream& outputFile){
    Maze *temp = new Maze(_maze);

	if(!_path->isEmpty()) {
        _path->remove();
    	while(!_path->isEmpty()){
	        if(_path->getSize() == 1){
	            break;
	        }
	        Cell curr = _path->peek();
	        curr._type = visited;
            curr.determineContent();
            temp->add(curr, curr._row, curr._col);
	        _path->remove();
    	}
	}

    outputFile << temp->str();
    outputFile << endl;
}