#include <iostream>
#include <fstream>

using namespace std;

int main(){
	ifstream file("small_case.in");

	if(file.is_open()){
		while(!file.eof()){
			string st;
			file>>st;
			cout<<"string read from file: "<<st<<endl;
		}
		file.close();
	}
	return 0;
}