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
  string tokenizeLocation(string);
  void handleCommand(string);
  void makeDirectory();
  void changeDirectory();
  void copyFile();
  void displayFiles();
  void createFile();
  void editFile();
  void renameFile();
  void showContent();
};

Emulator::Emulator() {
  _outputFile = ofstream("test.out");
  _name = "";
  _curr = _t.root();
}

void Emulator::handleCommand(string cmd) {
  _prev = _curr;

  if(cmd.find("mkdir ") != string::npos) {
    _name = cmd.substr(6);
    makeDirectory();
  } 
  else if(cmd.find("cd ") != string::npos) {
    _name = cmd.substr(3);
    changeDirectory();
  } 
  else if(cmd.find("ls") != string::npos) {
    _curr->display(_outputFile);
  } 
  else if(cmd.find("rm ") != string::npos) {
    _name = cmd.substr(3);

  } 
  else if(cmd.find(">> ") != string::npos) {
    _name = cmd.substr(3);
    editFile();
  } 
  else if(cmd.find("> ") != string::npos) {
    _name = cmd.substr(2);
    createFile();
  } 
  else if(cmd.find("edit ") != string::npos) {
    _name = cmd.substr(3);
    editFile();
  } 
  else if(cmd.find("rn ") != string::npos) {
    _name = cmd.substr(3);
    renameFile();
  } 
  else if(cmd.find("show ") != string::npos) {
    _name = cmd.substr(5);
    showContent();
  } 
  else if(cmd.find("whereis ") != string::npos) {
    _name = cmd.substr(8);

  }
  else if(cmd.find("mv ") != string::npos) {
    _name = cmd.substr(3);

  } 
  else if(cmd.find("cp ") != string::npos) {
    _name = cmd.substr(3);
    copyFile();
  }
  else if(cmd == "mkdir") {
    _outputFile << "usage: mkdir <directory name>" << endl;
  }
  else if(cmd == "cp") {
    _outputFile << "usage: cp source_file/source_directory target_file/target_directory" << endl;
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

  if(location.find("/root") != string::npos) {
    _curr = _t.root();
    location.erase(0, 6);
  }

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

  if(location == "..") {
    _curr = _curr->_parent;
  } else {
    _curr = _curr->getNode(location); 
  }
}

string Emulator::tokenizeLocation(string location) {
  while(location.find("/") != string::npos) {
    size_t tok = location.find("/");

    location.erase(0, location.substr(0, tok).length() + 1);
  }

  return location;
}

void Emulator::makeDirectory() {
  // checks if directory already exists
  if(_curr->getNode(_name) != NULL) {
    _outputFile << "mkdir: " << _name <<": Already exists" << endl;
  } 
  
  // checks if input is nested
  else if(_name.find("/") != string::npos) {
    Node *temp = parentFolder(_name);
    _name = tokenizeLocation(_name);
    Node *n = new Node(_name, directory);
    _t.insert(n, temp);
  } 
  else {
    Node *n = new Node(_name, directory);
    _t.insert(n, _curr);
  }
}

void Emulator::changeDirectory() {
  // checks if input is nested
  if(_name == "..") {
    _curr = _curr->_parent;
  }
  else if(_name.find("/") != string::npos) {
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

void Emulator::copyFile() {
  size_t tok = _name.find(" ");
  string fileName = _name.substr(0, tok);
  string newFileName = _name.substr(tok + 1);

  Node *original = _curr->getNode(fileName);
  Node *n;

  if(newFileName.find("/") != string::npos) {
    Node *temp = parentFolder(newFileName);
    newFileName = tokenizeLocation(newFileName);
    n = new Node(newFileName, original->_item.type());
    _t.insert(n, temp);
  } else {
    n = new Node(newFileName, original->_item.type());
    _t.insert(n, _curr);
  }

  if(original->_item.type() == file) {
    n->_item.writeContent(original->_item.content());
  }
}

void Emulator::displayFiles() {
  if(_name.find("/") != string::npos) {
    changeDirectory();
  }

  _curr->display(_outputFile);
}

void Emulator::createFile() {
  // if already exists
  if(_curr->getNode(_name) != NULL) {
    Node *n = _curr->getNode(_name);
    string content;

    while(true) {
      cin >> content;

      if(content == ":x")
        break;

      n->_item.writeContent(content);
    }

    n->_item.writeContent(content);
  } 
  else {
    Node *n = new Node(_name, file);
    string content;

    while(true) {
      cin >> content;

      if(content == ":x")
        break;

      n->_item.writeContent(content);
    }

    _t.insert(n, _curr);
  }
}

void Emulator::editFile() {
  Node *n = _curr->getNode(_name);

  string content;

  while(true) {
    cin >> content;

    if(content == ":x")
      break;

    n->_item.appendContent(content);
  }
}

void Emulator::showContent() {
  Node *n = _curr->getNode(_name);
  _outputFile << n->_item.content() << endl;
}

void Emulator::renameFile() {
  size_t tok = _name.find(" ");
  string fileName = _name.substr(0, tok);
  string newFileName = _name.substr(tok + 1);

  Node *n = _curr->getNode(fileName);

  n->_item.rename(newFileName);
}