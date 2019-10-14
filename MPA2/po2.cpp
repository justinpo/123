#include "book.hpp"

using namespace std;

int main() {
	string filename, temp, lines;

	cin >> filename;

  ifstream file(filename);

  if(file.is_open()){

		while(getline(file, temp)) {
			lines.append(temp);
		}

		file.close();
	}

	ofstream outputFile("poems.in");

	Book b(lines);
	b.display(outputFile);
}