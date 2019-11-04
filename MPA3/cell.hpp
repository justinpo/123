#include <string>
#include <iostream>

using namespace std;

enum cellType {
  wall,
  source,
  destination,
  open,
  visited
};

class Cell {
public:
  cellType _type;
  char _content;
  int _row;
  int _col;
  bool _visited;

  Cell();
  Cell(Cell*);
  Cell(cellType, int, int);
  void determineContent();
  void visit();
};


Cell::Cell() {
  _visited = false;
}

Cell::Cell(cellType type, int row, int col) {
  _type = type;
  determineContent();
  _row = row;
  _col = col;
  _visited = false;
}

Cell::Cell(Cell *cell) {
  _type = cell->_type;
  _content = cell->_content;
  _row = cell->_row;
  _col = cell->_col;
  _visited = cell->_visited;
}

void Cell::determineContent() {
  switch(_type) {
    case wall:
      _content = '#';
      break;
    case source:
      _content = 'o';
      break;
    case destination:
      _content = '*';
      break;
    case open:
      _content = '.';
      break;
    case visited:
      _content = 'x';
      break;
    default:
      break;
  }
}

void Cell::visit() {
  _visited = true;
  _type = visited;
  determineContent();
}