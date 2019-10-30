enum cellType {
  wall,
  source,
  destination,
  open,
  visited
}

class Cell {
public:
  cellType _type;
  char _content;
  int[2] _location;
  bool _visited;

  Cell();
  Cell(cellType, int[2]);
  void determineContent(cellType);
}

Cell::Cell(cellType type, int location[2]) {
  _type = type;
  determineContent(_type);
  location[0] = location[0];
  location[1] = location[1];
  _visited = false;
}

Cell::Cell() {
  _visited = false;
}

void Cell::determineContent(cellType type) {
  switch(type) {
    case "wall":
      _content = '#';
      break;
    case "source":
      _content = 'o';
      break;
    case "destination":
      _content = '*';
      break;
    case "open":
      _content = '.';
      break;
    case "visited":
      _content = 'x';
      break;
    default:
      break;
  }
}