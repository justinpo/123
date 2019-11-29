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

class FileDescriptor {
private:
  fileType _type;
  Date _dateCreated;
  Date _dateModified;

public:
  FileDescriptor(fileType, Date);
  string type();
  string dateCreated();
  void modify(Date);
};

Date::Date(int year, int month, int day) {
  _year = year;
  _month = month;
  _day = day;
}

string Date::str() {
  return to_string(_day) + "/" + to_string(_month) + "/" + to_string(_year);
}

FileDescriptor::FileDescriptor(fileType type, Date dateCreated) {
  _type = type;
  _dateCreated = dateCreated;
}

string FileDescriptor::type() {
  if(_type == file)
    return "file";
  else
    return "directory";  
}

string FileDescriptor::dateCreated() {
  return _dateCreated.str();
}

void FileDescriptor::modify(Date dateModified) {
  _dateModified = dateModified;
}