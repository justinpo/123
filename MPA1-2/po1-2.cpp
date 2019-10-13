#include <vector>
#include "polynomial.hpp"

using namespace std;

int main() {
	vector <string> forLoops;
	string filename, temp, lines, loopString, timeComplexity = "";
	bool infinite = false;

	cin >> filename;

  ifstream file(filename);

  if(file.is_open()){

		while(getline(file, temp)) {
			lines.append("\n");
			lines.append(temp);
		}

		file.close();
	}

	lines = removeSpaces(lines);

	while(lines.length() > 0) {
		int forCount = 0, closingCount = 0, i = 0;

		for(i = 0; i < lines.length(); i++) {
			if(forCount == closingCount && forCount != 0 && closingCount != 0)
				break;

			if (lines[i] == 'f' && lines[i+1] == 'o') {
				forCount++;
			} else if (lines[i] == '}') {
				closingCount++;
			}
		}

		forLoops.push_back(lines.substr(0, i));
		lines.erase(0,i);
	}

	for(int i = 0; i < forLoops.size() && !infinite; i++) {
		Loop loop;

		if(loop.getTimeComplexity(forLoops.at(i)) == "infinite")
			infinite = true;

		timeComplexity += loop.getTimeComplexity(forLoops.at(i));

		if(i + 1 != forLoops.size())
			timeComplexity += " + ";
	}

	if(!infinite) {
		Polynomial poly(timeComplexity);
		poly.simplify();
		cout << "T(n) = ";
		poly.display();
	} else {
		cout << "T(n) = infinite" << endl;
	}

	return 0;
}