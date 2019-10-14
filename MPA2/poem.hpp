#include "packets.hpp"

class Poem {
private:
  list<Packets> _poem;
  string _address;
  
public:
  Poem();
  Poem(string);

  string address();

  void append(Packets);
  void removeDuplicates();
  void display(ofstream&);
};


Poem::Poem() {
  _poem.clear();
  _address = "";
}

Poem::Poem(string address) {
  _poem.clear();
  _address = address;
}

void Poem::append(Packets p) {
  list<Packets>::iterator it;

  for (it = _poem.begin(); it != _poem.end(); ++it){
    if(p.sequenceNum() < it->sequenceNum())
      break;
  }

  _poem.insert(it, p);
}

void Poem::display(ofstream& outputFile) {
  removeDuplicates();

  list<Packets>::iterator it = _poem.begin();
  list<Packets>::iterator prev = _poem.begin();

  if(it->sequenceNum() != 0) {
    outputFile << "[title missing]" << endl;
  } else {
    it->display(outputFile);
    it++;
  }

  outputFile << it->address() << endl;

  for ( ; it != _poem.end(); ++it){
    int prevSequence = prev->sequenceNum();
    int currentSequence = it->sequenceNum();

    if(prevSequence != currentSequence - 1) {
      for(int i = prevSequence; i < currentSequence - 1; i++)
        outputFile << "[line missing]" << endl;
    }

    if(it->length() != 0) {
      it->display(outputFile);
    }
    
    prev = it;
  }
}

string Poem::address() {
  return _address;
}

void Poem::removeDuplicates() {
  for(list<Packets>::iterator i = _poem.begin(); i != _poem.end(); ++i) {
    list<Packets>::iterator j = i;
    j++;
    
    for( ; j != _poem.end(); ++j) {
      if(i->sequenceNum() == j->sequenceNum())
        _poem.erase(j++);
    }
  }
}