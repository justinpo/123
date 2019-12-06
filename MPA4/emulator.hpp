#include "tree.hpp"

class Emulator {
public:
  Tree _t;
  Node* _prev;
  Node* _curr;
  string _name;
  ofstream _outputFile;

  Emulator();
  // general functions
  Node* parentFolder(string);
  void goToDirectory(string);
  string tokenizeLocation(string);
  void handleCommand(string);
  // command specific functions
  void makeDirectory();
  void changeDirectory();
  void copyFile();
  void displayFiles();
  void createFile();
  void editFile();
  void renameFile();
  void showContent();
  void moveFile();
  void removeFile();
  void findFile();
};

Emulator::Emulator() {
  _outputFile = ofstream("test.out");
  _name = "";
  _curr = _t.root();
}

// function that handles all the commands passed to the emulator
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
  else if(cmd.find("ls ") != string::npos) {
    _name = cmd.substr(3);
    displayFiles();
  }
  else if(cmd.find("ls") != string::npos) {
    _name = "";
    displayFiles();
  } 
  else if(cmd.find("rm ") != string::npos) {
    _name = cmd.substr(3);
    removeFile();
  } 
  else if(cmd.find("rmdir ") != string::npos) {
    _name = cmd.substr(6);
    removeFile();
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
    _name = cmd.substr(5);
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
    findFile();
  }
  else if(cmd.find("mv ") != string::npos) {
    _name = cmd.substr(3);
    moveFile();
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
  else if(cmd == "rm") {
    _outputFile << "usage: rm <filename>" << endl;
  }
  else if(cmd == "rn") {
    _outputFile << "usage: rn <filename> <new filename>" << endl;
  }
  else if(cmd == "whereis") {
    _outputFile << "usage: whereis <filename/directory>" << endl;
  }
  else if(cmd == "rmdir") {
    _outputFile << "usage: rmdir <directory name>" << endl;
  }
  else if(cmd == "edit") {
    _outputFile << "usage: edit <filename>" << endl;
  }
  else if(cmd == "show") {
    _outputFile << "usage: show <filename>" << endl;
  }
  else {
    _outputFile << "Invalid command" << endl;
  }
}

// function that returns the parent folder of the given location
// say /root/cmsc/assignments was the location, it would return
// the node that points to cmsc
Node* Emulator::parentFolder(string location) {
  Node *temp = _curr;

  // checks if input is nested
  while(location.find("/") != string::npos) {
    size_t tok = location.find("/");

    string folder = location.substr(0, tok);

    if(folder == "..") {
      if(temp->_parent != NULL) {
        temp = temp->_parent;
      }
    } else {
      temp = temp->getNode(folder);
    }

    location.erase(0, folder.length() + 1);
  }

  return temp;
}

// function that changes _curr to the directory given,
// say /root/cmsc/assignments was the location, it would change
// _curr to assignments
void Emulator::goToDirectory(string location) {
  string folder;

  // checks if it starts from the root
  if(location.find("/root") != string::npos) {
    _curr = _t.root();
    location.erase(0, 6);
  }
  // checks if input is nested
  while(location.find("/") != string::npos) {
    size_t tok = location.find("/");

    folder = location.substr(0, tok);

    if(folder == "..") {
      if(_curr->_parent != NULL) {
        _curr = _curr->_parent;
      }
    } else {
      _curr = _curr->getNode(folder);
    }

    location.erase(0, folder.length() + 1);
  }

  if(location == "..") {
    if(_curr->_parent != NULL) {
      _curr = _curr->_parent;
    }
  } else {
    _curr = _curr->getNode(location); 
  }
}

// function that tokenizes a location,
// say /root/cmsc/assignments was the location, it would
// return a string containing assignments
string Emulator::tokenizeLocation(string location) {
  while(location.find("/") != string::npos) {
    size_t tok = location.find("/");

    location.erase(0, location.substr(0, tok).length() + 1);
  }

  return location;
}

void Emulator::makeDirectory() {
  // checks if input is nested
  if(_name.find("/") != string::npos) {
    Node *temp = parentFolder(_name);
    _name = tokenizeLocation(_name);
    // checks if directory already exists
    if(temp->getNode(_name) != NULL) {
      _outputFile << "mkdir: " << _name <<": Already exists" << endl;
    } else {
      Node *n = new Node(_name, directory);
      _t.insert(n, temp);
    }
  } 
  else {
    // checks if directory already exists
    if(_curr->getNode(_name) != NULL) {
      _outputFile << "mkdir: " << _name <<": Already exists" << endl;
    } else {
      Node *n = new Node(_name, directory);
      _t.insert(n, _curr);
    }
  }
}

void Emulator::changeDirectory() {
  // checks if input is nested
  if(_name == "..") {
    if(_curr->_parent != NULL) {
      _curr = _curr->_parent;
    }
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

  // checks if input is nested
  if(newFileName.find("/") != string::npos) {
    Node *temp = parentFolder(newFileName);
    newFileName = tokenizeLocation(newFileName);
    n = new Node(newFileName, original->_item.type());
    _t.insert(n, temp);
  } 
  else {
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
  if(_name.find("*") != string::npos) {
    string filter = tokenizeLocation(_name);
    _curr->filteredDisplay(_outputFile, filter);
  } else {
    _curr->display(_outputFile);
  }
}

void Emulator::createFile() {
  // if already exists
  if(_curr->getNode(_name) != NULL) {
    Node *n = _curr->getNode(_name);
    n->_item.eraseContent();
    string content;

    while(true) {
      getline(cin, content);

      if(content == ":x")
        break;

      n->_item.writeContent(content + "\n");
    }
  } 
  else {
    Node *n = new Node(_name, file);
    string content;

    while(true) {
      getline(cin, content);

      if(content == ":x")
        break;

      n->_item.writeContent(content + "\n");
    }

    _t.insert(n, _curr);
  }
}

void Emulator::editFile() {
  Node *n = _curr->getNode(_name);

  string content;

  while(true) {
    getline(cin, content);

    if(content == ":x")
      break;

    n->_item.writeContent(content + "\n");
  }
}

void Emulator::showContent() {
  Node *n = _curr->getNode(_name);
  _outputFile << n->_item.content();
}

void Emulator::renameFile() {
  size_t tok = _name.find(" ");
  string fileName = _name.substr(0, tok);
  string newFileName = _name.substr(tok + 1);

  Node *n = _curr->getNode(fileName);

  n->_item.rename(newFileName);
}

void Emulator::moveFile() {
  size_t tok = _name.find(" ");
  string fileName = _name.substr(0, tok);
  string newLocation = _name.substr(tok + 1);

  Node *file = _curr->getNode(fileName);
  Node *temp = _curr;

  if(newLocation.find("/") != string::npos) {
    temp = parentFolder(newLocation);
    newLocation = tokenizeLocation(newLocation);
  }

  temp = temp->getNode(newLocation);

  if(temp == NULL) {
    file->_item.rename(newLocation);
    return;
  } 
  else {
    _t.insert(file, temp);
    _t.remove(file->_item.name(), temp);
  }
}

void Emulator::removeFile() {  
  Node *temp = _curr;

  // checks if input is nested
  if(_name.find("/") != string::npos) {
    temp = parentFolder(_name);
    _name = tokenizeLocation(_name);
  }

  if(_name.find("*")) {
    _t.filteredRemove(_name, temp);
  } else if(temp->getNode(_name) != NULL) {
    _t.remove(_name, temp);
  }
  
}

void Emulator::findFile() {
  Node *curr = _t.root();
  stack<Node*> s, results;
  s.push(curr);

  while(!s.empty()) {
    curr = s.top();
    s.pop();

    if(curr->_item.name() == _name) {
      results.push(curr);
    }

    if(!curr->_children.empty()) {
      for(auto i : curr->_children) {
        s.push(i);
      }
    }
  }

  while(!results.empty()) {
    stack<string> path;

    curr = results.top();
    results.pop();
    path.push(curr->_item.name());

    while(curr->_parent != NULL) {
      curr = curr->_parent;
      path.push(curr->_item.name());
    }

    while(!path.empty()) {
      _outputFile << "/" << path.top();
      path.pop();
    }
    _outputFile << endl;
  }
}