#include "agenda.hpp"

class Maze {
public:
  Cell **_cells;
  int _rows;
  int _columns;

  Maze();
  Maze(Maze*);
  Maze(int, int);
  Maze(const Maze&);
  ~Maze();

  void fill(int, int);
  void add(Cell, int, int);

  Cell start();
  string str();
};

Maze::Maze() {
  _rows = 0;
  _columns = 0;
}

Maze::Maze(int rows, int columns) {
  fill(rows, columns);
}

Maze::Maze(Maze *maze) {
  fill(maze->_rows, maze->_columns);

  for(int i = 0; i < _rows; i++){
      for(int j = 0; j < _columns; j++){
        _cells[i][j] = maze->_cells[i][j];
      }
  }
}

Maze::Maze(const Maze& maze) {
    _rows = maze._rows;
    _columns = maze._columns;

    for(int i = 0; i < _rows; i++){
        for(int j = 0; j < _columns; j++){
          _cells[i][j] = maze._cells[i][j];
        }
    }
}

Maze::~Maze() {
  for(int i = 0; i < _rows; i++) {
      delete[] _cells[i];
  }
  delete[] _cells;
}

void Maze::fill(int rows, int columns) {
  _rows = rows;
  _columns = columns;

  _cells = new Cell*[_rows];
    for(int i = 0; i < _rows; i++)
      _cells[i] = new Cell[_columns];
}

void Maze::add(Cell cell, int row, int column) {
  _cells[row][column] = cell;
}

Cell Maze::start() {
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _columns; j++) {
      if (_cells[i][j]._type == source) {
        return _cells[i][j];
      }
    }
  }

  return _cells[0][0];
}

string Maze::str() {
  string mazeString = "";

  for(int i = 0; i < _rows; i++) {
    for(int j = 0; j < _columns; j++) {
      mazeString += _cells[i][j]._content;
    }
    mazeString += '\n';
  }
  
  return mazeString;
}