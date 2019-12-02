#include <string>

using namespace std;

enum fileType {
  file,
  directory
};

class Date {
private:
  int _year;
  int _month;
  int _day;

public:
  Date(int, int, int);
  string str();
};

Date::Date(int year, int month, int day) {
  _year = year;
  _month = month;
  _day = day;
}

string Date::str() {
  return to_string(_day) + "/" + to_string(_month) + "/" + to_string(_year);
}

class FileDescriptor {
private:
  string _name;
  string _content;
  fileType _type;
  Date _dateCreated;

public:
  FileDescriptor(string, fileType, Date);
  fileType type();
  string name();
  string content();
  string dateCreated();
};

FileDescriptor::FileDescriptor(string name, fileType type, Date dateCreated) {
  _name = name;
  _content = "";
  _type = type;
  _dateCreated = dateCreated;
}

fileType FileDescriptor::type() {
  return _type;
}

string FileDescriptor::name() {
  return _name;
}

string FileDescriptor::content() {
  return _content;
}

string FileDescriptor::dateCreated() {
  return _dateCreated.str();
}