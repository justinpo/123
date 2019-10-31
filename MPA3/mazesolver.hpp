#include "maze.hpp"
#include "agenda.hpp"

template <class T>
class Mazesolver {
private:
    Agenda<T> *_agenda;
    Maze *_maze;
public:
    Mazesolver();
    Mazesolver(Maze);
    ~Mazesolver();
    void solve();
    void writeSolution();
};

template <class T>
Mazesolver::Mazesolver(Maze maze) {
    _agenda = new Agenda<T>();
    _maze = maze;
}