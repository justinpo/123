// maze should represent the maze. 
// The maze has a size, its dimension (number of rows and columns).  
// The maze will simply be represented with a 2-dimensional array of squares, 
// its size defined by its dimension. Notice that the size of the maze is variable. 
// This means that the allocation of the 2d array should be dynamic.
// Also, figure out the parameter list of the constructor. 
// It should have a tostring operation that returns the maze as a string.

#include "cell.hpp"

class Maze {
private:
  Cell **_cells;
  int _dimension[2];

public:
  Maze();
  Maze(int[][]);
  string string();
  void append(Cell);
}

Maze::Maze() {
  _dimension[2] = {0};
}

Maze::Maze(int dimension[2]) {
  _dimension[0] = dimension[0];
  _dimension[1] = dimension[1];
}

string Maze::string() {
  string mazeString;

  for(int i = 0; i < _dimension[0]; i++) {
    for(int j = 0; i < _dimension[1]; i++) {
      mazeString += _cells[i][j].type;
    }
    mazeString += "\n";
  }
  
  return mazeString;
}

void Maze::append(Cell cell) {
  
}