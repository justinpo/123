#include "emulator.hpp"

using namespace std;

int main() {

  Emulator e;

  string cmd;

  ifstream file("test.in");

  if(file.is_open()) {
    while(getline(file, cmd)) {
      e.handleCommand(cmd);
    }
  }
}