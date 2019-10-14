#include "poem.hpp"
#include <vector>

class Book {
private:
  list<Poem> _book;
  vector<string> _addresses;

public:
  Book();
  Book(string);

  void display(ofstream&);
  bool checkAddress(string);
};

Book::Book() {
  _book.clear();
  _addresses.clear();
}

Book::Book(string bits) {
  while(bits.length() > 0) {
    int i = 0;

    for(i = 0; bits[i] != '\n' && bits[i] != '\r'; i++);

    Packets packet(bits.substr(0, i));

    string address = packet.address();

    if(checkAddress(address)) {
      list<Poem>::iterator it;
      for (it = _book.begin(); it != _book.end(); ++it){
        if(it->address() == address)
          break;
      }
      it->append(packet);
    } else {
      Poem *p = new Poem(address);
      p->append(packet);
      _book.push_back(*p);
      _addresses.push_back(address);
    }
    
    bits.erase(0, i + 1);
  }
}

void Book::display(ofstream& outputFile) {
  list<Poem>::iterator it;
  for (it = _book.begin(); it != _book.end(); ){
    it->display(outputFile);
    if(++it != _book.end()) {
      outputFile << endl;
      outputFile << "--------------------------------------------------------------------------------" << endl;
      outputFile << endl;
    }
  }
}

bool Book::checkAddress(string address) {
  int size = _addresses.size();
  for (int i = 0; i < size; i++){
    if(_addresses.at(i) == address)
      return true;
  }
  return false;
}