#include "tree.hpp"

using namespace std;

int main() {

  Tree t;

  while(true) {
    string cmd;

    cin >> cmd;

    if(cmd.find("mkdir ") != string::npos) {
      string name = cmd.substr(6);
      t.insert(name, directory);

    } else if(cmd.find("cd ") != string::npos) {
      string name = cmd.substr(3);
      
    } else if(cmd.find("rm ") != string::npos) {
      string name = cmd.substr(3);

    } else if(cmd.find("> ") != string::npos) {
      string name = cmd.substr(2);
      t.insert(name, file);

    } else if(cmd.find(">> ") != string::npos) {
      string name = cmd.substr(3);

    } else if(cmd.find("edit ") != string::npos) {
      string name = cmd.substr(3);

    } else if(cmd.find("rn ") != string::npos) {
      string name = cmd.substr(3);

    } else if(cmd.find("show ") != string::npos) {
      string name = cmd.substr(5);

    } else if(cmd.find("whereis ") != string::npos) {
      string name = cmd.substr(8);

    } else if(cmd.find("cp ") != string::npos) {
      string name = cmd.substr(3);
      
    }
  }
}