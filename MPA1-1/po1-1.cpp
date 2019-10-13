#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

class Loop {
public:
	Loop();

	// getter functions
	bool getLoop(istream&, string);
	bool getInitializers(string);
	bool getConditions(string);
	bool getIterator(string);
	bool getOperations(string);

	// utilities
	void printContent();
	int getEnd(string, int, char);
	string removeSpaces(string);
	bool clean();

private:
	string _initializer;
	string _conditions;
	string _iterator;
	string _operations;
};

int main() {
	string filename;

	cin >> filename;

  ifstream file(filename);

	cout << endl;
  
  if(file.is_open()){
		string lines;

		while(getline(file, lines)){
			if(lines.find("for") != string::npos) {
				Loop loop;
				loop.getLoop(file, lines);
				loop.printContent();
			}
		}

		file.close();

		return true;
	}
}

Loop::Loop() {
	_initializer = "";
	_conditions = "";
	_iterator = "";
	_operations = "";
}

bool Loop::getLoop(istream& file, string forString) {
	string loop, lines;
	bool tokenized = false;

	loop.append(forString);

	while(getline(file, lines) && !tokenized) {
		if(lines.find("}") != string::npos) {
			tokenized = true;
		}

		loop.append("\n");
		loop.append(lines);
	}

	getInitializers(loop);
	getConditions(loop);
	getIterator(loop);
	getOperations(loop);

	clean();

	if(_iterator == "") {
		char iter = _initializer[0];
		string search = ";";
		search.push_back(iter);

		int pos = _operations.find(search) + 1;
		int end = getEnd(_operations, pos, ';');

		_iterator = _operations.substr(pos, end - pos);
		_operations.erase(pos, (end + 1) - pos);
	}

	return true;
}

bool Loop::getInitializers(string loop) {
	int pos = loop.find("int") + 3;
	int end = getEnd(loop, pos, ';');

	_initializer = loop.substr(pos, end - pos);

	return true;
}

bool Loop::getConditions(string loop) {
	int pos = loop.find(_initializer) + _initializer.length() + 1;

	while(loop[pos] == ' ')
		pos++;

	int end = getEnd(loop, pos, ';');

	_conditions = loop.substr(pos, end - pos);

	cout << _conditions << endl;

	return true;
}

bool Loop::getIterator(string loop) {
	int pos = loop.find(_conditions) + _conditions.length() + 1;

	while(loop[pos] == ' ')
		pos++;

	int end = getEnd(loop, pos, ')');

	_iterator = loop.substr(pos, end - pos);

	return true;
}

bool Loop::getOperations(string loop) {
	int pos = loop.find("{") + 1;
	int end = getEnd(loop, pos, '}');

	_operations = loop.substr(pos, end - pos);

	return true;
}

void Loop::printContent() {
	cout << "initializer: " << _initializer << endl;
	cout << "conditions: " << _conditions << endl;
	cout << "iterator: " << _iterator << endl;
	cout << "operations: " << _operations << endl;
	cout << endl;
}

string Loop::removeSpaces(string str) {
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	str.erase(remove(str.begin(), str.end(), '\r'), str.end());
	str.erase(remove(str.begin(), str.end(), '\n'), str.end());

	return str;
}

int Loop::getEnd(string str, int pos, char delimiter) {
	int end;
	bool found = false;

	for(int i = pos; !found; i++) {
		if(str[i] == delimiter) {
			end = i;
			found = true;
		}
	}

	return end;
}

bool Loop::clean() {
	_initializer = removeSpaces(_initializer);
	_conditions = removeSpaces(_conditions);
	_iterator = removeSpaces(_iterator);
	_operations = removeSpaces(_operations);

	return true;
}