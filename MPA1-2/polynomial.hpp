#include "loop.hpp"
#include <iostream>
#include <vector>

using namespace std;

class Term {
public:
	Term();
	Term(string);
  bool setCoefficient(int);

	int getCoefficient();
	float getExponent();
	string getVar();
  void display();

private:
	int _coefficient;
	string _var;
  float _exponent;
};

class Polynomial {
public:
	Polynomial();
	Polynomial(string);

  void display();
	void simplify();
  void sort();

private:
	vector <Term> _polynomial;
};

Term::Term() {
	_coefficient = 0;
	_var = "";
  _exponent = 0;
}

Term::Term(string str) {
  int coefPos = -1;

	for(int i = 0; i < str.length(); i++) {
		if((str[i] >= '0' && str[i] <= '9' && str[i+1] != ')' && str[i-1] != '/') || str[i] == '-') {
      coefPos++;
		} else {
      _var += str.substr(i, 1);
		}
	}

  if(coefPos != -1)
    _coefficient = stoi(str.substr(0, coefPos + 1));
  
  if(_var.find("log") != string::npos) {
    _var = " " + _var.substr(0, 6) + " " + _var.substr(_var.length() - 1, 1);
  } else if(_var.find("rt(n)") != string::npos) {
    _var = " " + _var;
  }

  if(_var == "n") {
    _exponent = 1;
  } else {
    for(int i = 0; i < _var.length(); i++) {
      if(_var[i] >= '0' && _var[i] <= '9') {
        if(_var.find("log") != string::npos) {
          _exponent -= stoi(_var.substr(i, 1));
        } else if(_var.find("sqrt(n)") != string::npos) {
          _exponent = 1/2;
        }
        else {
          _exponent += stoi(_var.substr(i, 1));
        }
      }
    }
  }
}

bool Term::setCoefficient(int coef) {
  _coefficient = coef;

  return true;
}

void Term::display() {
  if(_coefficient != 0)
    cout << _coefficient;
  cout << _var;
}

int Term::getCoefficient() {
  return _coefficient;
}

string Term::getVar() {
  return _var;
}

int Term::getExponent() {
  return _exponent;
}

Polynomial::Polynomial() {
	_polynomial.clear();
}

Polynomial::Polynomial(string str) {
  str = removeSpaces(str);
  string temp = "";

	for(int i = 0; i < str.length(); i++) {
    
		if(str[i] != '+' && str[i] != '-') {
			temp += str.substr(i, 1);
		} else if(str[i] == '-') {
			Term term(temp);
			_polynomial.push_back(term);
      temp.clear();
			temp += str.substr(i, 1);
		} else if(str[i] == '+') {
			Term term(temp);
			_polynomial.push_back(term);
			temp.clear();
			continue;
		}
	}

  Term term(temp);
  _polynomial.push_back(term);
}

void Polynomial::display() {
  for(int i = 0; i < _polynomial.size(); i++) {
    if(_polynomial.at(i).getCoefficient() < 0 && i > 0) {
      _polynomial.at(i).setCoefficient(_polynomial.at(i).getCoefficient()*-1);
      cout << "- ";
    } else if(_polynomial.at(i).getCoefficient() > 0 && i > 0) {
      cout << "+ ";
    }
		_polynomial.at(i).display();
    cout << " ";
	}

  cout << endl;
}

void Polynomial::simplify() {
  for(int i = 0; i < _polynomial.size(); i++) {
    int currCoef = _polynomial.at(i).getCoefficient();
    string currVar = _polynomial.at(i).getVar();

    for(int j = i + 1; j < _polynomial.size(); j++) {
      if(_polynomial.at(j).getVar() == currVar) {
        currCoef += _polynomial.at(j).getCoefficient();
        _polynomial.erase(_polynomial.begin() + j);
        j--;
      }
    }

    _polynomial.at(i).setCoefficient(currCoef);
  }
}

void Polynomial::sort() {
  for(int i = 0; i < _polynomial.size(); i++) {
    int currExpo = _polynomial.at(i).getExponent();

    for(int j = 0; j < i; j++) {
      if(_polynomial.at(j).getExponent() > currExpo) {
        _polynomial.insert(_polynomial.begin() + j);
        j--;
      }
    }
  }
}