#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool readFile(string, ofstream&);

int main(){
	ofstream outputFile("test.out");
  readFile("inputFile.cpp", outputFile);

	outputFile.close();

  return 0;
}

bool readFile(string fileName, ofstream& outputFile){
	ifstream file(fileName);

	if(file.is_open()){
		string lines;
		while(getline(file, lines)){
			if(lines.find("#include") != string::npos) {
				int length = lines.length() - 2;
				int pos = lines.find('"') + 1;
        string newFile = lines.substr(pos, length - pos);
        readFile(newFile, outputFile);
        continue;
      }

			outputFile << lines << endl;
		}

		file.close();

		return true;
	}

	return false;
}