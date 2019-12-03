#include <string>

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