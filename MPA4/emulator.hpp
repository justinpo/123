#include "tree.hpp"

class Emulator {
public:
  Tree _t;
  Node* _prev;
  Node* _curr;
  string _name;
  ofstream _outputFile;

  Emulator();
  Node* parentFolder(string);
  void goToDirectory(string);
  void tokenizeName();
  void handleCommand(string);
};

Emulator::Emulator() {
  _outputFile = ofstream("test.out");
  _name = "";
}

void Emulator::handleCommand(string cmd) {
  _prev = _curr;

  if(cmd.find("mkdir ") != string::npos) {
    _name = cmd.substr(6);

    // checks if directory already exists
    if(_curr->getNode(_name) != NULL) {
      _outputFile << "mkdir: " << _name <<": Already exists" << endl;
    } 
    // checks if input is nested
    else if(_name.find("/") != string::npos) {
      Node *temp = parentFolder(_name);
      tokenizeName();
      _t.insert(_name, directory, temp);
    } 
    
    else {
      _t.insert(_name, directory, _curr);
    }
  } 
  else if(cmd.find("cd ") != string::npos) {
    _name = cmd.substr(3);

    Node *temp;

    // checks if input is nested
    if(_name.find("/") != string::npos) {
      goToDirectory(_name);
    } 
    else {
      _curr = _curr->getNode(_name);
    }

    // checks if folder exists
    if(_curr == NULL) {
      _outputFile << "cd: " << _name << ": No such file or directory" << endl;
      _curr = _prev;
    }
  } 
  else if(cmd.find("ls") != string::npos) {
    _curr->display(_outputFile);
  } 
  else if(cmd.find("rm ") != string::npos) {
    _name = cmd.substr(3);

  } 
  else if(cmd.find("> ") != string::npos) {
    _name = cmd.substr(2);

  } 
  else if(cmd.find(">> ") != string::npos) {
    _name = cmd.substr(3);

  } 
  else if(cmd.find("edit ") != string::npos) {
    _name = cmd.substr(3);

  } 
  else if(cmd.find("rn ") != string::npos) {
    _name = cmd.substr(3);

  } 
  else if(cmd.find("show ") != string::npos) {
    _name = cmd.substr(5);

  } 
  else if(cmd.find("whereis ") != string::npos) {
    _name = cmd.substr(8);

  } 
  else if(cmd.find("cp ") != string::npos) {
    _name = cmd.substr(3);
    
  }
  else if(cmd == "mkdir") {
    _outputFile << "usage: mkdir <directory name>" << endl;
  }
  else {
    _outputFile << "Invalid command" << endl;
  }
}

Node* Emulator::parentFolder(string location) {

  Node *temp = _curr;

  while(location.find("/") != string::npos) {
    size_t tok = location.find("/");

    string folder = location.substr(0, tok);

    if(folder == "..") {
      temp = temp->_parent;
    } else {
      temp = temp->getNode(folder);
    }

    location.erase(0, folder.length() + 1);
  }

  return temp;
}

void Emulator::goToDirectory(string location) {

  string folder;

  while(location.find("/") != string::npos) {
    size_t tok = location.find("/");

    folder = location.substr(0, tok);

    if(folder == "..") {
      _curr = _curr->_parent;
    } else {
      _curr = _curr->getNode(folder);
    }

    location.erase(0, folder.length() + 1);
  }

  _curr = _curr->getNode(folder);
}

void Emulator::tokenizeName() {
  while(_name.find("/") != string::npos) {
    size_t tok = _name.find("/");

    _name.erase(0, _name.substr(0, tok).length() + 1);
  }
}