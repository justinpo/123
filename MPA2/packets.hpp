#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <list>
#include <vector>

using namespace std;

class Packets {
private:
  string _packet;
  string _source;
  string _destination;
  int _sequenceNum;
  string _checksum;
  int _length;
  string _data;
  bool _corrupted;
  
public:
  Packets();
  Packets(string);
  void setSource(string);
  void setDestination(string);
  void setSequenceNum(string);
  void setChecksum(string);
  void setLength(string);
  void setData(string);

  int length();
  int sequenceNum();
  void display(ofstream&);
  string address();

  string bitsToAddress(string);
  string addBinary(string, string);
  string onesComplement(string);
};

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

Packets::Packets() {
  _packet = "";
  _source = "";
  _destination = "";
  _sequenceNum = 0;
  _checksum = "";
  _length = 0;
  _data = "";
  _corrupted = false;
}

Packets::Packets(string bits) {
  _packet = bits;
  setSource(bits.substr(0, 32));
  bits.erase(0, 32);
  setDestination(bits.substr(0, 32));
  bits.erase(0, 32);
  setSequenceNum(bits.substr(0, 16));
  bits.erase(0, 16);
  setChecksum(bits.substr(0, 16));
  bits.erase(0, 16);

  if(!_corrupted) {
    setLength(bits.substr(0, 16));
    bits.erase(0, 16);
    setData(bits.substr(0, _length));
    bits.erase(0, _length);
  } else
    _data = "[line corrupted]";
}

void Packets::setSource(string bits) {
  _source = bitsToAddress(bits);
}

void Packets::setDestination(string bits) {
  _destination = bitsToAddress(bits);
}

void Packets::setSequenceNum(string bits) {
  bitset<16> sequenceNum(bits);
  _sequenceNum = sequenceNum.to_ulong();
}

void Packets::setChecksum(string bits) {
  _checksum = bits;
  string tempPacket = "";
  tempPacket += _packet;
  tempPacket.replace(80, 16, "0000000000000000");

  string binaryOne = tempPacket.substr(0, 16);
  tempPacket.erase(0, 16);

  while(tempPacket.length() > 0) {
    string binaryTwo = tempPacket.substr(0, 16);
    tempPacket.erase(0, 16);

    binaryOne = addBinary(binaryOne, binaryTwo);
  }

  binaryOne = onesComplement(binaryOne);

  if(binaryOne != _checksum)
    _corrupted = true;
}

void Packets::setLength(string bits) {
  bitset<16> length(bits);
  _length = length.to_ulong();
}

void Packets::setData(string bits) {
  while(bits.length() > 0) {
    bitset<8> character(bits.substr(0, 8));
    bits.erase(0, 8);
    char c = char(character.to_ulong());
    _data += c;
  }
}

string Packets::bitsToAddress(string bits) {
  bitset<8> octetOne(bits.substr(0, 8));
  bitset<8> octetTwo(bits.substr(8, 8));
  bitset<8> octetThree(bits.substr(16, 8));
  bitset<8> octetFour(bits.substr(24, 8));

  string address = to_string(octetOne.to_ulong()) + '.' + to_string(octetTwo.to_ulong()) + '.' + to_string(octetThree.to_ulong()) + '.' + to_string(octetFour.to_ulong());

  return address;
}

string Packets::addBinary(string binaryOne, string binaryTwo) {
  string output;
  int carry = 0, sum = 0;

  binaryOne.insert(0, "0");
  binaryTwo.insert(0, "0");

  for(int i = 16; i >= 0; i--) {
    if (binaryOne[i] == '1' && binaryTwo[i] == '1' && carry == 0) {
      sum = 0;
      carry = 1;
    } else if (binaryOne[i] == '1' && binaryTwo[i] == '1' && carry == 1) {
      sum = 1;
      carry = 1;
    } else {
      string one(1, binaryOne[i]);
      string two(1, binaryTwo[i]);

      sum = stoi(one) + stoi(two);

      if (sum == 1 && carry == 1) {
        sum = 0;
        carry = 1;
      } else if (sum == 0 && carry == 1) {
        sum = 1;
        carry = 0;
      }
    }

    output.insert(0, to_string(sum));
  }

  if(output[0] == '1')
    output = addBinary(output.erase(0, 1), "0000000000000001");
  else 
    output.erase(0, 1);

  return output;
}

string Packets::onesComplement(string bits) {
  int length = bits.length();

  for (int i = 0; i < length; i++) {
    if (bits[i] == '0')
      bits[i] = '1';
    else if (bits[i] == '1')
      bits[i] = '0';
  }

  return bits;
}

int Packets::length() {
  return _length;
}

int Packets::sequenceNum() {
  return _sequenceNum;
}

string Packets::address() {
  return _source + '/' + _destination;
}

void Packets::display(ofstream& outputFile) {
  outputFile << _data << endl;
}

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

    if(prevSequence != currentSequence - 1 && currentSequence - prevSequence < 100) {
      for(int i = prevSequence; i < currentSequence; i++)
        outputFile << "[line missing]" << endl;
    }

    if(it->length() == 0) {
      if(currentSequence > 100)
        it->display(outputFile);
    } else
      it->display(outputFile);

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
        _poem.erase(j);
    }
  }
}

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
    if(++it != _book.end())
      outputFile << "--------------------------------------------------------------------------------" << endl;
      outputFile << endl;
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