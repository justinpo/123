#include "mazesolver.hpp"

cellType determineType(char);

int main() {
  int cases, row, col;
  char content;

  ifstream inputFile("maze.in");
  ofstream outputFile("maze.out");

  if(inputFile.is_open()) {

		inputFile >> cases;

		for (int i = 0; i < cases; i++) {
      inputFile >> row;
      inputFile >> col;

      Maze *maze = new Maze(row, col);

      for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
          inputFile >> content;
          Cell temp(determineType(content), i, j);
          maze->add(temp, i, j);
        }
      }

      Mazesolver<queue<Cell>> queueMaze(maze);
      queueMaze.solve();
      queueMaze.writeSolution(outputFile);
      
      Mazesolver<stack<Cell>> stackMaze(maze);
      stackMaze.solve();
      stackMaze.writeSolution(outputFile);
		}

    inputFile.close();
  }
}

cellType determineType(char content) {
  switch(content) {
    case '#':
      return wall;
    case 'o':
      return source;
    case '*':
      return destination;
    case '.':
      return open;
    case 'x':
      return visited;
    default:
      break;
  };

  return wall;
}