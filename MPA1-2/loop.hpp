#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// utilities
int getEnd(string, int, char);
string removeSpaces(string);

// enums
enum variablesType {
	intInt,
	intVar,
	varInt,
};

enum conditionType {
	lessThan,
	greaterThan,
	lessThanEqual,
	greaterThanEqual,
};

enum iteratorType {
	addOne,
	subtractOne,
	add,
	subtract,
	multiply,
	divide,
};

enum loopType {
	normal,
	nested
};

class Initializer {
public:
	Initializer();
	bool setInitializer(string);
	string getVar();
	string getValue();
	string getString();

private:
	string _var;
	string _value;
	string _string;
};

class Condition {
public:
	Condition();
	bool setCondition(string);
	string getModifier();
	string getEquality();
	string getBound();
	string getString();    

private:
	string _modifier;
	string _equality;
	string _bound;
	string _string;
};

class Iterator {
public:
	Iterator();
	bool setIterator(string);
	string getOperation();
	string getValue();
	string getString();

private:
	string _operation;
	string _value;
	string _string;
};

class Loop {
public:
	Loop();

	// setter functions
	bool setLoop(string);
	bool setInitializer(string);
	bool setConditions(string);
	bool setIterator(string);
	bool setProcesses(string);
	bool setTimeComplexity();
	void setType();

	// getter functions
	int getLineCount(string);
	string getTimeComplexity(string);

	// utilities
	void printContent();

private:
	Initializer _initializer;
	Condition _condition;
	Iterator _iterator;
	string _processes;
	string _timeComplexity;
	int _type[4] = {0, 0, 0, 0};
};

Initializer::Initializer() {
	_value = "";
}

bool Initializer::setInitializer(string str) {
	_string = str;
	_var = str.substr(0, 1);

	int pos = str.find("=") + 1;
	_value = str.substr(pos, str.length() - pos);

	return true;
}

string Initializer::getVar() {
	return _var;
}

string Initializer::getValue() {
	return _value;
}

string Initializer::getString() {
	return _string;
}

Condition::Condition() {
	_modifier = "";
	_equality = "";
	_bound = "";
}

bool Condition::setCondition(string str) {
	int exponentCount = 1;

	_string = str;

	int modifierEnd = str.find(">") != string::npos ? str.find(">") : str.find("<");

	_modifier = str.substr(0, modifierEnd - 0);
	_equality = str.find("=") != string::npos ? str.substr(_modifier.length(), 2): _equality = str.substr(_modifier.length(), 1);
	_bound = str.substr(_modifier.length() + _equality.length(), str.find(";") - (_modifier.length() + _equality.length()));

	for(int i = 0; i < _modifier.length(); i++) {
		if(_modifier[i] == '*')
			exponentCount++;
	}

	if(exponentCount > 1) {
		_modifier = _modifier[0];
		_modifier += '^';
		_modifier += to_string(exponentCount);
	}

	return true;
}

string Condition::getModifier() {
	return _modifier;
}

string Condition::getEquality() {
	return _equality;
}

string Condition::getBound() {
	return _bound;
}

string Condition::getString() {
	return _string;
}

Iterator::Iterator() {
	_operation = "";
	_value = "";
}

bool Iterator::setIterator(string str) {
	_string = str;

	int operationStart;

	for(int i = 1; i < str.length(); i++) {
		if(str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*') {
			operationStart = i;
			break;
		}
	}

	_operation = str.substr(operationStart, 2);

	if(str.length() > 2)
		_value = str.substr(3, str.length() - 3);

	return true;
}

string Iterator::getOperation() {
    return _operation;
}

string Iterator::getValue() {
    return _value;
}

string Iterator::getString() {
    return _string;
}

Loop::Loop() {
	_processes = "";
}

bool Loop::setLoop(string forString) {

	setInitializer(forString);
	setConditions(forString);
	setProcesses(forString);
	setIterator(forString);
	setType();
	setTimeComplexity();

	return true;
}

bool Loop::setInitializer(string loop) {
	int pos = loop.find("int") + 3;
	int end = getEnd(loop, pos, ';');

	_initializer.setInitializer(loop.substr(pos, end - pos));

	return true;
}

bool Loop::setConditions(string loop) {
	int pos = loop.find(_initializer.getString()) + _initializer.getString().length() + 1;

	int end = getEnd(loop, pos, ';');

	_condition.setCondition(loop.substr(pos, end - pos));

	return true;
}

bool Loop::setIterator(string loop) {
	int pos = loop.find(_condition.getString()) + _condition.getString().length() + 1;

	int end = getEnd(loop, pos, ')');

    if(loop.substr(pos, end - pos).length() == 0) {
		string search = ";";
		search += _initializer.getVar()[0];

		int pos = _processes.find(search) + 1;
		int end = getEnd(_processes, pos, ';');

		_iterator.setIterator(_processes.substr(pos, end - pos));
		_processes.erase(pos, (end + 1) - pos);

	} else
			_iterator.setIterator(loop.substr(pos, end - pos));

	return true;
}

bool Loop::setProcesses(string loop) {
	int pos = loop.find("{") + 1;
	int end = loop.length();

	_processes = loop.substr(pos, end - pos);

	return true;
}

void Loop::printContent() {
	cout << "initializer: " << _initializer.getValue() << endl;
	cout << "conditions: " << _condition.getModifier() << " " << _condition.getEquality() << " " << _condition.getBound() << endl;
	cout << "iterator: " << _iterator.getOperation() << " " << _iterator.getValue() << endl;
	cout << "operations: " << _processes << endl;
	cout << endl;
}

string removeSpaces(string str) {
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	str.erase(remove(str.begin(), str.end(), '\r'), str.end());
	str.erase(remove(str.begin(), str.end(), '\n'), str.end());

	return str;
}

int Loop::getLineCount(string str) {
	int count = 0, i = 0;

	for(i = 0; i < str.length(); i++) {
		if(str[i] == '>' || str[i] == '<' || str[i] == '=' || str[i] == '*' || str[i] == '/' || str[i] == '+' || str[i] == '-') {

			if(str[i + 1] == '>' || str[i + 1] == '<' || str[i + 1] == '=' || str[i + 1] == '*' || str[i + 1] == '/' || str[i + 1] == '+' || str[i + 1] == '-') {
				i++;
				count++;
				continue;
			}

			count++;
		}
	}

	return count;
}

bool Loop::setTimeComplexity() {

	_timeComplexity = "";

	if(_type[3] == 1) {
		Loop nestedLoop;
		int pos = _processes.find("for");
		int end = _processes.find("}") + 1;

		string nested = _processes.substr(pos, end - pos);
		string nestedComplexity = nestedLoop.getTimeComplexity(nested);

		_timeComplexity = nestedComplexity + " ";

		_processes.erase(pos, nested.length() - pos);
	}

	int loopTime = getLineCount(_condition.getString()) 
								+ getLineCount(_iterator.getString()) 
								+ getLineCount(_processes);

	if((_type[0] == 0 || _type[0] == 1) && (_type[1] == 0 || _type[1] == 2) && (_type[2] == 1 || _type[2] == 3 || _type[2] == 5) ||
		(_type[0] == 2 && (_type[1] == 1 || _type[1] == 3) && (_type[2] == 0 || _type[2] == 2 || _type[2] == 4))) {

		_timeComplexity += "infinite";

	} else if((_type[0] == 0 || _type[0] == 1) && (_type[1] == 1 || _type[1] == 3) ||
		(_type[0] == 2 && (_type[1] == 0 || _type[1] == 2))) {

		_timeComplexity += "2";

	} else if(_type[0] == 0 && (_type[1] == 0 || _type[1] == 2) && (_type[2] == 0 || _type[2] == 2)) {
		int a = stoi(_initializer.getValue());
		int b = stoi(_condition.getBound());
		int c = _type[1] == 0 ? 2 : 1;

		if(_type[2] == 0) {
			_timeComplexity += to_string((loopTime * (b - (a - c))) 
											+ getLineCount(_initializer.getString()) 
											+ getLineCount(_condition.getString()));
		} else if(_type[2] == 2) {
			_timeComplexity += to_string((loopTime * (b - (a - c))/stoi(_iterator.getValue())) 
											+ getLineCount(_initializer.getString()) 
											+ getLineCount(_condition.getString()));
		}

	} else if(_type[0] == 1 && (_type[1] == 0 || _type[1] == 2) && (_type[2] == 0 || _type[2] == 2)) {
		int a = stoi(_initializer.getValue());
		int c = _type[1] == 0 ? 2 : 1;

		_timeComplexity += to_string(loopTime);

		if(_condition.getModifier().find("^2") != string::npos)
			_timeComplexity += " sqrt(n)";
		else if(_condition.getModifier().find("^3") != string::npos)
			_timeComplexity += " cubert(n)";
		else
			_timeComplexity += "n";

		int constant = -(loopTime * (a - c)) + getLineCount(_initializer.getString()) + getLineCount(_condition.getString());

		if(_iterator.getValue() != "" && _type[2] == 2) {
			_timeComplexity += "/";
			_timeComplexity += _iterator.getValue();
		}

		if(constant < 0) {
			_timeComplexity += " - ";
			constant *= -1;
		} else
			_timeComplexity += " + ";
			_timeComplexity += to_string(constant);

	} else if((_type[0] == 1 || _type[0] == 2) && (_type[1] == 0 || _type[1] == 2) && _type[2] == 4) {
		int a = stoi(_initializer.getValue());
		int c = _type[1] == 0 ? 2 : 1;

		_timeComplexity += to_string(loopTime);
		_timeComplexity += " log(" + _iterator.getValue() + ") n";

		int constant = -(loopTime * (a - c)) + getLineCount(_initializer.getString()) + getLineCount(_condition.getString());

		if(constant < 0) {
			_timeComplexity.append(" - ");
			constant *= -1;
		} else
			_timeComplexity.append(" + ");

		_timeComplexity += to_string(constant);
	}

	return true;
}

string Loop::getTimeComplexity(string str) {

	setLoop(str);

	return _timeComplexity;
}

void Loop::setType() {
	variablesType varType;
	conditionType condType;
	iteratorType iterType;
	loopType loType;

	// for varType
	if(_initializer.getValue() != "n" && _condition.getBound() != "n")
		varType = intInt;
	else if(_initializer.getValue() != "n" && _condition.getBound() == "n")
		varType = intVar;
	else if(_initializer.getValue() == "n" && _condition.getBound() != "n")
		varType = varInt;
	
	// for condType
	if(_condition.getEquality() == "<")
		condType = lessThan;
	else if(_condition.getEquality() == ">")
		condType = greaterThan;
	else if(_condition.getEquality() == "<=")
		condType = lessThanEqual;
	else if(_condition.getEquality() == ">=")
		condType = greaterThanEqual;

	// for iterType
	if(_iterator.getOperation() == "++")
			iterType = addOne;
	else if(_iterator.getOperation() == "--")
			iterType = subtractOne;
	else if(_iterator.getOperation() == "+=")
			iterType = add;
	else if(_iterator.getOperation() == "-=")
			iterType = subtract;
	else if(_iterator.getOperation() == "*=")
			iterType = multiply;
	else if(_iterator.getOperation() == "/=")
			iterType = divide;

	// for loopType
	if(_processes.find("for") != string::npos) {
		loType = nested;
	}

	_type[0] = varType;
	_type[1] = condType;
	_type[2] = iterType;
	_type[3] = loType;
}

int getEnd(string str, int pos, char delimiter) {
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