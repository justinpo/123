#include <string>
#include <iostream>

using namespace std;

enum fileType {
  file,
  directory
};

class File {
private:
  string _name;
  string _content;
	string _location;
  fileType _type; 

public:
  File();
  File(string, fileType);
  fileType type();
  string name();
  string content();
  void rename(string);
  void writeContent(string);
  void appendContent(string);
};

File::File() {
  _name = "";
  _content = "";
  _location = "";
  _type = directory;
}

File::File(string name, fileType type) {
  _name = name;
  _content = "";
  _type = type;
}

fileType File::type() {
  return _type;
}

string File::name() {
  return _name;
}

string File::content() {
  return _content;
}

void File::rename(string newName) {
  _name = newName;
}

void File::writeContent(string content) {
  _content += content;
}

void File::appendContent(string content) {
  _content += content;
}