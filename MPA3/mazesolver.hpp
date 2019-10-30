class Mazesolver{
private:
    Agenda *a;
    Maze *m;
public:
    Mazesolver();
    ~Mazesolver();
    void solve();
    void writeSolution();
};